# FROM osrf/ros:noetic-desktop-full
FROM ros:noetic
ARG DEBIAN_FRONTEND=noninteractive
# commande initial message de préparation
# ENTRYPOINT ["echo","container_is_ready"]

# Mise à jour et installation des paquets nécessaires
# RUN apt-get update && apt-get install -y --no-install-recommends \
#     git \
#     python3-pip \
#     && rm -rf /var/lib/apt/lists/*

USER root

RUN apt-get update

RUN apt-get install -y build-essential sudo terminator iproute2 gedit lsb-release lsb-core wget nano

# RUN apt-get install git &&  apt-get install python3-pip
# RUN echo "ALL DONE"
# # install ros packages
# RUN apt-get update && apt-get install -y --no-install-recommends \
#     ros-noetic-desktop-full=1.5.0-1* \
#     && rm -rf /var/lib/apt/lists/*

RUN adduser user
RUN adduser user sudo
#remove password
RUN passwd -d user

USER user

# Commande pour maintenir le conteneur actif (ici, lancement de roscore)
WORKDIR /projects_ros
# CMD ["roscore"]