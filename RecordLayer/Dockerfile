# This Dockerfile is intended for the end user.
# Our CI system is using another one in .docker/build

FROM ubuntu:focal

# Install the dependencies of Project Everest
RUN apt-get update
RUN apt-get --yes --no-install-recommends install software-properties-common dirmngr gpg-agent
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
RUN echo "deb https://download.mono-project.com/repo/ubuntu stable-focal main" | tee /etc/apt/sources.list.d/mono-official-stable.list
RUN apt-get update
RUN apt-get --yes install --no-install-recommends opam emacs gcc binutils make m4 git time gnupg ca-certificates mono-devel sudo

# Create a new user and give them sudo rights
RUN useradd -d /home/test test
RUN echo 'test ALL=NOPASSWD: ALL' >> /etc/sudoers
RUN mkdir /home/test
RUN chown test:test /home/test
USER test
ENV HOME /home/test
WORKDIR $HOME

SHELL ["/bin/bash", "--login", "-c"]

# Install OCaml
ENV OPAMYES 1
RUN opam init --disable-sandboxing --compiler=4.09.1
RUN opam env --set-switch | tee --append .profile .bashrc .bash_profile

# Install emacs F* mode
ADD --chown=test package/fstar.sh bin/fstar.sh
ADD --chown=test package/init.el .emacs.d/init.el
ADD --chown=test package/install-fstar-mode.el .emacs.d/install-fstar-mode.el
RUN emacs --script .emacs.d/install-fstar-mode.el

# Add the project files proper
RUN mkdir quic-crypto
WORKDIR quic-crypto
ADD --chown=test src/*.fst src/*.fsti src/Makefile src/
ADD --chown=test hints/*.hints hints/
ADD --chown=test Makefile Makefile
ADD --chown=test Makefile.include Makefile.include
ADD --chown=test README.md README.md
ADD --chown=test test/main.c test/QUICTest.fst test/Makefile test/
ADD --chown=test noheader.txt noheader.txt
ADD --chown=test install-everest.sh install-everest.sh

# Clone and build Project Everest
ARG EVEREST_THREADS=1
RUN ./install-everest.sh
RUN cat everest-env.sh | tee --append $HOME/.profile $HOME/.bashrc $HOME/.bash_profile

ENTRYPOINT ["/bin/bash", "--login"]
