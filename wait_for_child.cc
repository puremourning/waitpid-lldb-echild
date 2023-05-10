#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <iostream>

int main( int argc, char** argv )
{
  pid_t p = fork();
  if ( p < 0 )
  {
    // error
    perror( "Failed to fork" );
    return p;
  }

  if ( p == 0 )
  {
    // child
    std::string line;
    while( std::cin >> line ) {
      std::cout << "You said: " << line << '\n';
    }
  }
  else
  {
    printf( "Child PID: %d", p );
    while (true)
    {
      int sts = 0;
      pid_t waited = waitpid( p, &sts, WNOHANG );
      if ( waited < 0 )
      {
        perror( "waitpid error" );
        return waited;
      }
      else if ( waited != p )
      {
        printf( "." );
        fflush( stdout );
      }
      else if ( WIFSTOPPED( sts ) )
      {
        printf( "The process was stopped by signal: %d\n", WSTOPSIG(sts) );
      }
      else if ( WIFEXITED( sts ) )
      {
        printf( "The process terminated with exit: %d\n", WEXITSTATUS( sts ) );
      }
      else if ( WIFSIGNALED( sts ) )
      {
        printf( "Child terminated with signal: %d\n", WTERMSIG( sts ) );
      }
      else
      {
        printf( "Unknwon reason for exit! %d/%d\n", waited, sts );
      }

      sleep(2);
    }
  }
}
