#include "lfsr.h"

void GLFSR_init(lfsr_t *glfsr, lfsr_data_t polynom, lfsr_data_t seed_value) {
    lfsr_data_t seed_mask;
    unsigned int shift = 8 * sizeof (lfsr_data_t) - 1;

    glfsr->polynomial = polynom | 1;
    glfsr->data = seed_value;

    seed_mask = 1;
    seed_mask <<= shift;

    while (shift--) {
        if (polynom & seed_mask) {
            glfsr->mask = seed_mask;
            break;
        }
        seed_mask >>= 1;
    }
    return;
}

unsigned char GLFSR_next(lfsr_t *glfsr) {
    unsigned char retval = 0;

    glfsr->data <<= 1;

    if (glfsr->data & glfsr->mask) {
        retval = 1;
        glfsr->data ^= glfsr->polynomial;
    }

    return retval ;
}
�� S>   �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[\\�[�[�[�[�[�[�[�[�[\\\$\\\	\\\�[�[�[�[�[�[�[�[�[�[�[�[�[�[\+\\\\\\\�[\\�[�[�[�[�[�[�[�[\\\2\1\/\+\?\G\/\\\�[�[�[�[�[�[�[�[�[�[\1\V\Z\V\[\V\H\?\3\+\\�[�[�[�[\\#\\ \\1\ \\\\$\+\\"\ \\	\\\\\�[�[�[�[\	\\\\�[�[�[�[\\\\\*\5\"\\�[�[�[\\6\Y\f\n\l\z\c\e\C\0\(\\�[�[\\.\H\+\.\
\\\:\H\U\W\K\N\O\=\<\!\\	\\0\>\K\i\n\Q\*\\�[\\9\[\e\h\`\p\l\=\\\�[�[�[�[�[&\Q\P\`\U\D\[\Z\R\F\#\$\\\�[ \\\\\\�[\\\\\\-\=\F\E\J\R\:\F\C\I\K\L\Q\b\L\O\D\B\8\-\\\\\.\"\\	\\$\\4\4\5\4\@\S\O\_\p\k\}\u\�\U\P\N\R\T\M\6\K\>\,\\\�[�[\&\?\?\P\G\S\I\?\M\U\r\�\�\�\�\y\T\@\!\\*\+\I\D\N\[\[\L\L\K\j\\�\}\�\}\Z\a\R\L\6\+\\\\
\\D\1\W\c\]\Z\?\8\(\6\B\U\o\�\�\�\s\r\g\=\)\!\\,\C\>\W\W\c\k\H\;\\\\%\7\M\Y\q\y\�\�\v\^\_\]\m\s\�\�\�\e\U\1\\�[�[�[�[�[\-\S\\\m\r\�\{\�\�\|\_\T\a\c\o\v\g\W\b\`\=\\
\�[�[�[�[�[�[\\9\o\�\�\�\�\�\�\�\q\f\k\H\H\K\<\K\Q\N\K\c\^\k\d\r\]\J\A\J\V\W\D\;\8\;\-\7\Q\n\Z\h\\�\�\�\{\e\m\�\o\s\�\z\~\z\f\b\P\`\F\C\P\Y\`\l\b\h\h\^\K\7\:\G\D\`\~\�\z\z\r\d\O\D\U\h\Q\9\G\O\g\{\y\p\h\c\X\Y\Q\J\J\B\g\r\s\p\h\v\f\j\P\U\t\�\�\�\�\�\�\z\f\i\k\[\g\�\�\�\j\u\}\}\n\v\�\�\�\�\�\�\�\�\�\t\k\b\Y\a\u\|\�\�\�\�\�\�\�\�\�\�\y\�\{\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\l\g\e\`\R\[\C\A\U\]\p\�\�\�\�\�\�\�\�\�\�\}\j\U\O\Z\a\j\k\s\w\}\�\}\�\~\�\�\�\�\�\�\�\~\�\�\�\q\|\p\y\~\�\{\�\h\g\p\~\�\�\�\�\�\�\�\�\�\�\�\�\k\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\n\{\m\j\s\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\r\�\�\�\�\�\�\{\m\h\]\]\t\o\�\�\�\�\�\�\�\\s\o\\\Z\O\O\P\X\y\�\�\|\}\u\|\g\u\t\w\�\�\�\�\�\�\�\�\�\�\�\�\�\�\\]\]\W\I\]\~\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\~\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\s\o\\\\e\f\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\��\�\s\x\�\�\�\�\�\�\�\��\�\�\�\�\�\�\�\�\�\�\s�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\��\�\�\�\�\�\�\�\�\�\�\��\�\�\�\�\ ]�\�\�\�\�\��\�\�\�\�\�\�\�\�\�\�\��\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\]]]�\\�\�\     1��,�,���S>   �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[\\�[�[�[�[�[�[�[�[�[\\\$\\\	\\\�[�[�[�[�[�[�[�[�[�[�[�[�[�[\+\\\\\\\�[\\�[�[�[�[�[�[�[�[\\\2\1\/\+\?\G\/\\\�[�[�[�[�[�[�[�[�[�[\1\V\Z\V\[\V\H\?\3\+\\�[�[�[�[\\#\\ \\1\ \\\\$\+\\"\ \\	\\\\\�[�[�[�[\	\\\\�[�[�[�[\\\\\*\5\"\\�[�[�[\\6\Y\f\n\l\z\c\e\C\0\(\\�[�[\\.\H\+\.\
\\\:\H\U\W\K\N\O\=\<\!\\	\\0\>\K\i\n\Q\*\\�[\\9\[\e\h\`\p\l\=\\\�[�[�[�[�[&\Q\P\`\U\D\[\Z\R\F\#\$\\\�[ \\\\\\�[\\\\\\-\=\F\E\J\R\:\F\C\I\K\L\Q\b\L\O\D\B\8\-\\\\\.\"\\	\\$\\4\4\5\4\@\S\O\_\p\k\}\u\�\U\P\N\R\T\M\6\K\>\,\\\�[�[\&\?\?\P\G\S\I\?\M\U\r\�\�\�\�\y\T\@\!\\*\+\I\D\N\[\[\L\L\K\j\\�\}\�\}\Z\a\R\L\6\+\\\\
\\D\1\W\c\]\Z\?\8\(\6\B\U\o\�\�\�\s\r\g\=\)\!\\,\C\>\W\W\c\k\H\;\\\\%\7\M\Y\q\y\�\�\v\^\_\]\m\s\�\�\�\e\U\1\\�[�[�[�[�[\-\S\\\m\r\�\{\�\�\|\_\T\a\c\o\v\g\W\b\`\=\\
\�[�[�[�[�[�[\\9\o\�\�\�\�\�\�\�\q\f\k\H\H\K\<\K\Q\N\K\c\^\k\d\r\]\J\A\J\V\W\D\;\8\;\-\7\Q\n\Z\h\\�\�\�\{\e\m\�\o\s\�\z\~\z\f\b\P\`\F\C\P\Y\`\l\b\h\h\^\K\7\:\G\D\`\~\�\z\z\r\d\O\D\U\h\Q\9\G\O\g\{\y\p\h\c\X\Y\Q\J\J\B\g\r\s\p\h\v\f\j\P\U\t\�\�\�\�\�\�\z\f\i\k\[\g\�\�\�\j\u\}\}\n\v\�\�\�\�\�\�\�\�\�\t\k\b\Y\a\u\|\�\�\�\�\�\�\�\�\�\�\y\�\{\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\l\g\e\`\R\[\C\A\U\]\p\�\�\�\�\�\�\�\�\�\�\}\j\U\O\Z\a\j\k\s\w\}\�\}\�\~\�\�\�\�\�\�\�\~\�\�\�\q\|\p\y\~\�\{\�\h\g\p\~\�\�\�\�\�\�\�\�\�\�\�\�\k\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\n\{\m\j\s\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\r\�\�\�\�\�\�\{\m\h\]\]\t\o\�\�\�\�\�\�\�\\s\o\\\Z\O\O\P\X\y\�\�\|\}\u\|\g\u\t\w\�\�\�\�\�\�\�\�\�\�\�\�\�\�\\]\]\W\I\]\~\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\\�\~\�\�\�\�\�\�\�\�\��\�\�\�\�\�\�\�\s\o\g\\e\f\�\�\�\�\�\�\�\�\�\��\�\�\�\�\�\�\�\�\�\�\�s\x\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\s\�\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\��\�\�\�\ ]�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\]]]�\��\�\     �K�,�,���S>   �[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[\\�[�[�[�[�[�[�[�[�[\\\$\\\	\\\�[�[�[�[�[�[�[�[�[�[�[�[�[�[\+\\\\\\\�[\\�[�[�[�[�[�[�[�[\\\2\1\/\+\?\G\/\\\�[�[�[�[�[�[�[�[�[�[\1\V\Z\V\[\V\H\?\3\+\\�[�[�[�[\\#\\ \\1\ \\\\$\+\\"\ \\	\\\\\�[�[�[�[\	\\\\�[�[�[�[\\\\\*\5\"\\�[�[�[\\6\Y\f\n\l\z\c\e\C\0\(\\�[�[\\.\H\+\.\
\\\:\H\U\W\K\N\O\=\<\!\\	\\0\>\K\i\n\Q\*\\�[\\9\[\e\h\`\p\l\=\\\�[�[�[�[�[&\Q\P\`\U\D\[\Z\R\F\#\$\\\�[ \\\\\\�[\\\\\\-\=\F\E\J\R\:\F\C\I\K\L\Q\b\L\O\D\B\8\-\\\\\.\"\\	\\$\\4\4\5\4\@\S\O\_\p\k\}\u\�\U\P\N\R\T\M\6\K\>\,\\\�[�[\&\?\?\P\G\S\I\?\M\U\r\�\�\�\�\y\T\@\!\\*\+\I\D\N\[\[\L\L\K\j\\�\}\�\}\Z\a\R\L\6\+\\\\
\\D\1\W\c\]\Z\?\8\(\6\B\U\o\�\�\�\s\r\g\=\)\!\\,\C\>\W\W\c\k\H\;\\\\%\7\M\Y\q\y\�\�\v\^\_\]\m\s\�\�\�\e\U\1\\�[�[�[�[�[\-\S\\\m\r\�\{\�\�\|\_\T\a\c\o\v\g\W\b\`\=\\
\�[�[�[�[�[�[\\9\o\�\�\�\�\�\�\�\q\f\k\H\H\K\<\K\Q\N\K\c\^\k\d\r\]\J\A\J\V\W\D\;\8\;\-\7\Q\n\Z\h\\�\�\�\{\e\m\�\o\s\�\z\~\z\f\b\P\`\F\C\P\Y\`\l\b\h\h\^\K\7\:\G\D\`\~\�\z\z\r\d\O\D\U\h\Q\9\G\O\g\{\y\p\h\c\X\Y\Q\J\J\B\g\r\s\p\h\v\f\j\P\U\t\�\�\�\�\�\�\z\f\i\k\[\g\�\�\�\j\u\}\}\n\v\�\�\�\�\�\�\�\�\�\t\k\b\Y\a\u\|\�\�\�\�\�\�\�\�\�\�\y\�\{\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\l\g\e\`\R\[\C\A\U\]\p\�\�\�\�\�\�\�\�\�\�\}\j\U\O\Z\a\j\k\s\w\}\�\}\�\~\�\�\�\�\�\�\�\~\�\�\�\q\|\p\y\~\�\{\�\h\g\p\~\�\�\�\�\�\�\�\�\�\�\�\�\k\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\n\{\m\j\s\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\r\�\�\�\�\�\�\{\m\h\]\]\t\o\�\�\�\�\�\�\�\\s\o\\\Z\O\O\P\X\y\�\�\|\}\u\|\g\u\t\w\�\�\�\�\�\�\�\�\�\�\�\�\�\�\\]\]\W\I\]\~\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�~\�\�\�\�\�\�\�\�\�\�\��\�\�\�\�\�\s\o\g\\\e\f�\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\s\\�\�\�\�\�\�\�\�\�\�\�\\�\�\�\�\�\�\�\s\�\�\��\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\\�\�\�\ ]�\�\�\�\�\�\�\\�\�\�\�\�\�\�\�\�\�\��\�\�\�\�\�\�\�\�\�\�\��\�\�\�\�\�\]]]�\�\��\     �7�=�=Ӡ� �   5\.\ \\\(\:\@\_\i\|\|\l\W\I\-\!\\\\*\/\3\7\#\\\ \O\H\?\S\Y\U\d\`\a\[\O\\�[ \\\\\\\7\:\>\5\3\6\-\<\H\S\