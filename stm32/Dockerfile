FROM alpine:3.5
MAINTAINER Oliver Bruns obruns@gmail.com

RUN apk update && \
    apk add --update \
        alpine-sdk \
        expat-dev \
        gmp-dev \
        mpc1-dev \
        mpfr-dev \
        ncurses-dev \
        python-dev \
        texinfo \
        zlib-dev \
        xz \
        xz-dev && \
    apk add \
        --update-cache \
        --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ \
        stlink

ENV BINUTILS binutils-2.27
ENV GCC gcc-6.3.0
ENV GDB gdb-7.12.1
ENV NEWLIB newlib-2.5.0
ENV TARGET arm-none-eabi

RUN mkdir /tmp/arm

ADD https://ftp.gnu.org/gnu/binutils/${BINUTILS}.tar.bz2 /tmp/arm
ADD https://ftp.gnu.org/gnu/gcc/${GCC}/${GCC}.tar.bz2 /tmp/arm
ADD https://ftp.gnu.org/gnu/gdb/${GDB}.tar.xz /tmp/arm
RUN cd /tmp/arm && \
    curl --remote-name ftp://sourceware.org/pub/newlib/${NEWLIB}.tar.gz && \
    tar -xjf ${BINUTILS}.tar.bz2 && \
    tar -xjf ${GCC}.tar.bz2 && \
    tar -xJf ${GDB}.tar.xz && \
    tar -xzf ${NEWLIB}.tar.gz

RUN cd /tmp/arm/${BINUTILS} && \
        ./configure \
          --target=${TARGET} \
          --with-cpu=cortex-m4 \
          --with-fpu=fpv4-sp-d16 \
          --with-float=hard \
          --with-mode=thumb \
          --enable-interwork \
          --enable-multilib \
          --with-gnu-as \
          --with-gnu-ld \
          --disable-nls && \
        make -j4 all && \
        make install && \
    cd /tmp/arm/${GCC} && \
        mkdir build1 && cd build1 && \
        ../configure \
          --target=${TARGET} \
          --with-cpu=cortex-m4 \
          --with-fpu=fpv4-sp-d16 \
          --with-float=hard \
          --with-mode=thumb \
          --enable-interwork \
          --enable-multilib \
          --with-system-zlib \
          --with-newlib \
          --without-headers \
          --disable-shared \
          --disable-nls \
          --with-gnu-as \
          --with-gnu-ld \
          --enable-languages="c" && \
        make -j4 all-gcc && \
        make install-gcc && \
    cd /tmp/arm/${NEWLIB} && \
        ./configure \
          --target=${TARGET} \
          --with-cpu=cortex-m4 \
          --with-fpu=fpv4-sp-d16 \
          --with-float=hard \
          --with-mode=thumb \
          --enable-interwork \
          --enable-multilib \
          --disable-newlib-supplied-syscalls \
          --with-gnu-as \
          --with-gnu-ld \
          --disable-nls \
          --disable-newlib-nano-malloc && \
        make -j4 all && \
        make install && \
    cd /tmp/arm/${GCC} && \
        mkdir build2 && cd build2 && \
        ../configure \
          --target=$TARGET \
          --with-cpu=cortex-m4 \
          --with-fpu=fpv4-sp-d16 \
          --with-float=hard \
          --with-mode=thumb \
          --enable-interwork \
          --enable-interwork \
          --enable-multilib \
          --with-system-zlib \
          --with-newlib \
          --disable-shared \
          --disable-nls \
          --with-gnu-as \
          --with-gnu-ld \
          --enable-languages="c,c++" && \
        make -j4 all && \
        make install && \
    cd /tmp/arm/${GDB} && \
        ./configure --target=${TARGET} && \
        make -j4 all && \
        make install && \
    rm -r /tmp/arm/${GCC} \
        /tmp/arm/${BINUTILS} \
        /tmp/arm/${GDB} \
        /tmp/arm/${NEWLIB} \
        /tmp/arm
