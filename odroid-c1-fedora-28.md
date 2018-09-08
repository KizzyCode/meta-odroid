# Create an ARM-compatible Fedora installation

## Install a linux distro on your ODROID-C1
```sh
# Download Ubuntu
wget http://de.eu.odroid.in/ubuntu_18.04lts/ubuntu-18.04.1-3.10-minimal-odroid-c1-20180802.img.xz

# Copy it do your SD-card; use `of=/dev/diskX bs=1M` (without r and capital M) for non-macOS
xz -d < ubuntu-18.04.1-3.10-minimal-odroid-c1-20180802.img.xz | sudo dd of=/dev/rdiskX bs=1m
```

## Prepare Ubuntu
```sh
# Setup network and time/date
# <Here!>

# Install update
apt-get update && apt-get upgrade && apt-get autoremove && apt-get clean

# Install dependencies
apt-get install parted
```

## Download Fedora minimal and decompress it
```sh
wget https://download.fedoraproject.org/pub/fedora/linux/releases/28/Spins/armhfp/images/Fedora-Minimal-armhfp-28-1.1-sda.raw.xz
unxz Fedora-Minimal-armhfp-28-1.1-sda.raw.xz
```

## Resize the Fedora image by +3GiB
```sh
# Append space to the raw image and attach it
dd if=/dev/zero bs=1M count=3072 oflag=dsync >> Fedora-Minimal-armhfp-28-1.1-sda.raw
losetup -f Fedora-Minimal-armhfp-28-1.1-sda.raw

# Scan for partitions and resize the physical root partition
partprobe /dev/loop0 # Use `losetup -l` to get your used loop-device
fdisk /dev/loop0
  > d # Delete a partition entry
  > 4   # Entry 4
  > n # Create a new partition
  > p   # Primary partition
  > ↵   # Default start
  > ↵   # Default length
  > n   # Do not remove the Ext4 signature
  > w # Write our changes

# Rescan partitions and resize the root-FS
partprobe /dev/loop0 # Reboot if necessary
e2fsck -f /dev/loop0p4
resize2fs /dev/loop0p4
```

## Mount the root-partition in `/mnt`, bind devices into the mounted partition, enable network and `chroot`
```sh
mount /dev/loop0p4 /mnt
mount -o bind /dev /mnt/dev
mount -o bind /dev/pts /mnt/dev/pts
mount -t sysfs /sys /mnt/sys
mount -t proc /proc /mnt/proc
cp /etc/resolv.conf /mnt/etc/resolv.conf
chroot /mnt
```

## Setup Fedora
```sh
# Install updates
dnf upgrade && dnf clean all
```

## Unmount the Fedora image and backup it on an external device
```sh
# Ctrl+D to leave the chroot-environment

# Unmount FS and detach loop device
umount /mnt
losetup -d /dev/loop0

# Backup Fedora-Minimal-armhfp-28-1.1-sda.raw !!!
```


# Create Fedora-SD card

## Build a yocto-linux (we need this because it builds a running and up-to-date kernel)
```sh
# Install the build requirements
dnf install gawk make wget tar bzip2 gzip python3 unzip perl patch \
     diffutils diffstat git cpp gcc gcc-c++ glibc-devel texinfo chrpath \
     ccache perl-Data-Dumper perl-Text-ParseWords perl-Thread-Queue perl-bignum socat \
     python3-pexpect findutils which file cpio python python3-pip xz

# Clone yocto
git clone -b master git://git.yoctoproject.org/poky.git yocto-odroid
cd yocto-odroid
git clone -b master git://github.com/akuster/meta-odroid # A backup of this repo can be found under git://github.com/KizzyCode/meta-odroid.git

# Setup yocto
source ./oe-init-build-env
bitbake-layers add-layer ../meta-odroid
echo 'MACHINE = "odroid-c2"' >> conf/local.conf

# Build yocto linux (this may take a while...)
bitbake core-image-base

# Your yocto-image is now in `tmp/deploy/images/odroid-c` (sth. like `core-image-base-odroid-c1.wic.xz`)
```

## Now write your yocto-linux to your SD card
```sh
xz -d < path-to-image/core-image-base-odroid-c1.wic.xz | sudo dd of=/dev/sdX bs=1M oflag=dsync
```

## Copy the Fedora-installation to the data partition
```sh
# Attach the Fedora image
sudo losetup -f Fedora-Minimal-armhfp-28-1.1-sda.raw
sudo partprobe /dev/loop0

# Copy the Fedora root partition to the yocto root partition
sudo dd if=/dev/loop0p4 bs=1M | sudo dd of=/dev/sdX2 bs=1M oflag=dsync
```

## Now the ODROID should be able to boot into fedora; now you can do some post-processing...
🎉
