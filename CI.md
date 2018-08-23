# Continuous Integration at CuteCom

For CuteCom development GitLab continuous integration is used.
This is controlled by [the gilab CI YAML file](./.gitlab-ci.yml).

After each push, the code will be checked within the CI pipeline.  
First of all, it is verified that the code adheres to the styleguide for this project by running `./run-clang-format.py -r .`.  
If there are any formating difference discovered, the pipeline will fail and no other jobs will be run.  
To accomplish this, the 'nsr' helper is used which was posted at this [GitLab Issue](https://gitlab.com/gitlab-com/support-forum/issues/1311).
The CI wrapper for 'clang-format' used was written by [Guillaume Papin](https://github.com/Sarcasm/run-clang-format).

In the next step it is checked that CuteCom can be build with a recent Qt5 version (version 5.11 at the time of writing this).  
The last step is verifying, that CuteCom can be build with Qt5 version 5.3 (on Debian Jessie) as this is the minimum requirement.

The CI pipeline is using two Docker images hand crafted for this purpose. They can be found on the [Docker Hub](https://hub.docker.com/u/cutecom/).  
These images are build from the Dockerfiles living [here (Debian)](https://gitlab.com/cutecom/jessie-qt5-build) and [here (openSuse)](https://gitlab.com/cutecom/opensuse-qt5-devel).  
Detailed instructions how the images are build and published are documented at the Dockerfile's repositories.

After setting up Docker on the local machine, it is possible to build a CuteCom binary within the image.  
The following is sort of a CheatSheet including useful docker commands as well as condensed instructions for running the docker image and building CuteCom inside.

```bash
# handling containers
$docker ps -a
$docker stop <ContainerID>
$docker start -i <ContainerID> #restarts a stopped container returning to the previous bash
$docker rm <ContainerID>

# handling images
$docker images
$docker rmi cutecom/opensuse-qt5-devel
$docker rmi <ImageID>

# volume handling
$docker volume create cutecom
$docker volume inspect cutecom

# running interative bash inside the image
# for details refer to the end of this code block
$docker run --privileged -i --mount source=cutecom,target=/git -t cutecom/opensuse-qt5-devel  /bin/bash

# we war now inside the container
docker:/ # cd /git/
docker:/git # git clone https://gitlab.com/cutecom/cutecom.git
docker:/git # cd cutecom
docker:/git/cutecom # cmake . && build
docker:/git/cutecom # exit

# the --privileged is important - otherwise rcc will fail complaining, the files declared in resources.qrc are missing
# /usr/lib64/qt5/bin/rcc --list resources.qrc
# see https://stackoverflow.com/questions/51027703/mxe-qt5-application-builds-fail-in-docker-container
```

## Cheveats
The second image is quite large. Presumably this could be stripped down.
I'm open for suggestions. Testing an image locally before using it on GitLab can be done as described in the CheatSheet above.  
There might different aproaches to e.g. inforce the styleguide (e.g. including it as a pre-commit/pre-push git hook). The advantage of including it into the CI pipeline is that it will be consistent for everyone contributing.