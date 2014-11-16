#!/bin/sh
# You can optionally connect to the VM with
# virt-viewer -c qemu:///system Debian7
export OS=Debian7v1

virt-install \
--connect qemu:///system \
--name ${OS} \
--ram 512 \
--vcpus 1 \
--file /tmp/${OS}.img \
--file-size=4 \
--location http://http.debian.net/debian/dists/stable/main/installer-amd64/ \
--virt-type kvm \
--os-variant debianwheezy \
--extra-args "auto=true hostname=${OS} domain=  url=http://subsole.org/static/misc/debian-preseed.cfg text"
