#include "philosophers.h"

static size_t digit_len(u_timestamp nb)
{
    size_t i;

    i = 1;
    while (nb / 10)
    {
        nb /= 10;
        ++i;
    }
    return (i);
}

static void    copy_int_as_str_to_buffer(u_timestamp nb, char **buffer)
{
    size_t  len;
    size_t  offset;

    len = digit_len(nb);
    offset = len;
    while (len)
    {
        (*buffer)[len - 1] = (nb % 10) + '0';
        --len;
        nb /= 10;
    }
    *buffer += offset;
}

static void copy_str_to_buffer(const char *str, char **buffer)
{
    size_t  i;

    if (str == NULL)
        return ;
    i = 0;
    while (str[i])
    {
        (*buffer)[i] = str[i];
        ++i;
    }
    *buffer += i;
}

static void buffer_state(const char *str, t_philo *philo, char **buffer)
{
    copy_int_as_str_to_buffer(get_time(), buffer);
    copy_str_to_buffer(" ms philosopher nb ", buffer);
    copy_int_as_str_to_buffer(philo->id, buffer);
    copy_str_to_buffer(str, buffer);
}

void    print_status(int philo_state, t_philo *philo)
{
    const char *state[6];
    char        *buffer_offset;
    char        buffer[BUFFER_SIZE];
    
    pthread_mutex_lock(&philo->data->ts_print);
    if (philo->data->is_end)
    {
        pthread_mutex_unlock(&philo->data->ts_print);
        return ;
    }
    buffer_offset = buffer;
    memset(buffer, 0, BUFFER_SIZE);
    state[SLEEPING] = " is sleeping\n";
    state[THINKING] = " is thinking\n";
    state[EATING] = " is eating\n";
    state[DIED] = " is dead\n";
    state[TOOK_LEFT_FORK] = " took left fork\n";
    state[TOOK_RIGHT_FORK] = " took right fork\n";
    if (philo_state == TOOK_FORKS)
    {
        buffer_state(state[TOOK_LEFT_FORK], philo, &buffer_offset);
        buffer_state(state[TOOK_RIGHT_FORK], philo, &buffer_offset);
    }
    else
        buffer_state(state[philo_state], philo, &buffer_offset);
    write(1, buffer, ft_strlen(buffer));
    pthread_mutex_unlock(&philo->data->ts_print);
}
