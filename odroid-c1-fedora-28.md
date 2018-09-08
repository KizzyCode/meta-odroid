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
dd if=/dev/zero bs=1M count=3072 >> Fedora-Minimal-armhfp-28-1.1-sda.raw
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

