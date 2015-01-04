#include <fcntl.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <cerrno>
#include <iostream>
#include <cassert>
#include <map>

using std::string;
using std::clog;
using std::endl;
using std::map;

const char* fsmda_semaphore_base_name = "/fsmda_semaphore_";
map<const string, sem_t*> named_semaphores;

void CreateNamedSemphoreHelper(const string& semaphore_name,
                               bool diferent_processes) {
  string semname = fsmda_semaphore_base_name + semaphore_name;
  clog << "CreateNamedSemphoreHelper::semname is " << semname
       << ",diferent_processes=" << diferent_processes << endl;

  // child wait for ParentPostSemphoreHelper call
  sem_t* aux_semaphore =
      sem_open(semname.c_str(), O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 0);
  if (aux_semaphore != SEM_FAILED) {
    clog << "CreateNamedSemphoreHelper::created new semaphore !" << endl;
  } else if (errno == EEXIST) {
    clog << "CreateNamedSemphoreHelper::semaphore appears to exist already, "
            "open existing semaphore !" << endl;
    aux_semaphore = sem_open(semname.c_str(), O_CREAT, S_IRUSR | S_IWUSR, 0);
  }
  assert(aux_semaphore != SEM_FAILED);

  // initialize named semaphore
  if (diferent_processes) {
    sem_init(aux_semaphore, 1, 0);
  } else {
    sem_init(aux_semaphore, 0, 0);
  }
  named_semaphores[semname] = aux_semaphore;
  int val = 0;
  sem_getvalue(aux_semaphore, &val);
  clog << "CreateNamedSemphoreHelper::semaphore's ptr is " << aux_semaphore
       << endl;
  clog << "CreateNamedSemphoreHelper::semaphore's value is " << val << endl;
}

void WaitNamedSemphoreHelper(const string& semaphore_name) {
  string semname = fsmda_semaphore_base_name + semaphore_name;
  clog << "WaitNamedSemphoreHelper::semname is " << semname << endl;
  clog << "WaitNamedSemphoreHelper::semaphore's ptr is "
       << named_semaphores[semname] << endl;

  int sts = sem_wait(named_semaphores[semname]);
  if (sts == 0)
    clog << "WaitNamedSemphoreHelper::sem_wait() succeeded!" << endl;
  else
    clog << "WaitNamedSemphoreHelper::sem_wait() failure" << endl;
}

void ReleaseNameSemphoreHelper(const string& semaphore_name) {
  string semname = fsmda_semaphore_base_name + semaphore_name;
  clog << "ReleaseNameSemphoreHelper::semname=" << semname << endl;
  sem_close(named_semaphores[semname]);
  sem_destroy(named_semaphores[semname]);
  sem_unlink(semname.c_str());
}

void PostNamedSemphoreHelper(const string& semaphore_name) {
  string semname = fsmda_semaphore_base_name + semaphore_name;
  clog << "PostNamedSemphoreHelper::semname=" << semname << endl;
  sem_t* aux_semaphore = sem_open(semname.c_str(), 0);
  assert(aux_semaphore != SEM_FAILED);
  sem_post(aux_semaphore);
  sem_close(aux_semaphore);
  sem_unlink(semname.c_str());
}
