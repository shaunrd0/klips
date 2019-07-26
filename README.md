# klips
Snippets that I frequently use and share

This repository is a collection of code snippets that I reuse, clone, or frequently refer to in regards to configurations or settings. This can be cloned as a whole and refered to locally as needed, or copied around and used to lay out templates for larger projects.

The snippets are organized within topic-labeled folders. 'plates' is short-hand for templates, and houses all folders / projects that can be copied and edited / adjusted locally as templates for larger projects.

Other directories could contain configuration files, bash exports, scripts, etc.

All snippets will be listed below with the directories in the master branch. If you are not on master, I cant guarentee anything will be anywhere unless otherwise described.

### Contents

```
https://github.com/shaunrd0/...

klips/
├──── plates/
│       ├── cpp-cmake (Simple cpp executable template, built using cmake)
│       └── cpp-launcher (Simple cpp launcher template, built using cmake. Easily expandable.)
│
├──── refs/
│       └── doxygenROT (Basic rule-of-thumb for Doxygen commenting)
│
├──── scripts/
│       └── cmake-build.sh (Script to toss around and build cmake projects)

# Copy / paste below symbols for editing this README / updating hierarchy

    │    ├    ─    └ 
```

###Scripts

I write these scripts for my own use, and you may need to tweak them slightly to suit your needs. 

Never run a script you can't read or understand. Comments can be found in the scripts, usually explaining them block-by-block. Below is my personal use cases for the scripts, to provide further insight into how I use them and how they might be useful to you.

####cmake-build.sh

I usually run this script within whatever directory I'm working in, hence the infinite loop, I leave the script running until I'm done with my work and move to a new directory / cmake project.



