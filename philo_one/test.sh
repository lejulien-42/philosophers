#!/bin/bash
make re
for i in 1 1 1 1 1 1;do
(./philo_one 4 410 200 200; pkill philo_one) &
done
make fclean
