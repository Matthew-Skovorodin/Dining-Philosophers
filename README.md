# Dining Philosophers 
Executes the Dining Philosophers problem using mutex variables and pthreads.

## Behavior
The program utilizes mutex variables and pthreads to address the classic Dining Philosophers problem. In this scenario, philosophers alternate between thinking and eating while contending for limited resources (chopsticks). Mutex variables ensure that only one philosopher can access a pair of chopsticks at a time, preventing conflicts and deadlock situations.
This implementation aims to provide a clear understanding of the Dining Philosophers problem and its resolution using concurrent programming concepts.

### Build
To compile the program, use the following command:
```bash
make all
```

### Run
Execute the compiled program with:
```bash
./main
```

### Clean
To remove the compiled files, run:
```bash
make clean
```


