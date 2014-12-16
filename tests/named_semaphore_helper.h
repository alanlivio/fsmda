#ifndef NAMED_SEMAPHORE_HELPER_H
#define NAMED_SEMAPHORE_HELPER_H

/*----------------------------------------------------------------------
 |   includes
 +---------------------------------------------------------------------*/
#include <string>

using std::string;

/*----------------------------------------------------------------------
 |   Global functions
 +---------------------------------------------------------------------*/
void CreateNamedSemphoreHelper(const string& semaphore_name, bool diferent_processes);
void WaitNamedSemphoreHelper(const string& semaphore_name);
void ReleaseNameSemphoreHelper(const string& semaphore_name);
void PostnamedSemphoreHelper(const string& semaphore_name);

#endif  // NAMED_SEMAPHORE_HELPER_H
