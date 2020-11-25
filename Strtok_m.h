#ifndef STRTOK_M_H
#define STRTOK_M_H
class Strtok_m{
public:

    char *strtok_fr (char *s, char delim, char **save_ptr)
    {
        char *tail;
        char c;

        if (s == NULL) {
            s = *save_ptr;
        }
        tail = s;
        if ((c = *tail) == '\0') {
            s = NULL;
        }
        else {
            do {
                if (c == delim) {
                    *tail++ = '\0';
                    break;
                }
            }while ((c = *++tail) != '\0');
        }
        *save_ptr = tail;
        return s;
    }


    char *strtok_f(char *s, char delim)
    {
        static char *save_ptr;

        return strtok_fr(s, delim, &save_ptr);
    }


};

#endif // STRTOK_M_H
