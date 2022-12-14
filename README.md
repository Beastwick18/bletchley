# Bletchley-Park-Assignment
- This assignment is for my Operating Systems class (CSE3320)
- In this assignment, I implemented a producer/consumer multithreaded decryptor
- For this assignment, all c files were included except for `main.c`
- The program is capable of handling 1024 threads and up to 6 messages at a time
- One thread is created as the producer, which gets the next file to be decrypted and puts it on the buffer
- Up to 1024 consumer threads read from the buffer, decrypt the message, and output to a file
- This functionality is accomplished by using semaphores and mutexes to prevent deadlocking with many threads running at once
