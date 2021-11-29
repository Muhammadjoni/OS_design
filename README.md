DATA STRUCTURE

A Unix File System volume is composed of the following parts:

A few blocks at the beginning of the partition reserved for boot blocks (which must be initialized
separately from the filesystem)

A superblock, containing a magic numberidentifying this as a UFS filesystem, and some other vital
numbers describing this filesystem's geometry and statistics and behavioral tuning parameters

A collection of cylinder groups. Each cylinder group has the following components:

- A backup copy of the superblock

- A cylinder group header, with statistics, free lists, etc., about this cylinder group, similar to those in the
superblock

- A number of inodes, each containing file attributes

- A number of data blocks

Inodes are numbered sequentially, starting at 0. Inode 0 is reserved for unallocated directory entries, inode
1 was the inode of the bad block file in historical UNIX versions, followed by the inode for the root
directory, which is always inode 2 and the inode for the lost+found directory which is inode 3.

Directory files contain only the list of filenames in the directory and the inode associated with each file. All
file metadata are kept in the inode.
