###############################################################################
## Author: Shaun Reed | Contact: shaunrd0@gmail.com | URL: www.shaunreed.com ##
##                                                                           ##
## A test script for using Git APIs and gitpython module                     ##
###############################################################################
# gittest.py

import git
import requests
import json


def local_status(path):
  repo = git.Repo(path)
  if repo.bare is True:
    print("Error loading repository located at %s, check that it is a repository\n" % path)
  else:
    print("Loaded local repository: %s\n\tOrigin URL: %s" % (repo.description, repo.remotes['origin']))
  return repo

def remote_status(user, repo):
  reply = requests.get('https://api.github.com/repos/%s/%s/commits' % (user, repo))
  commits = reply.json()
  remoteCommit = []
  remoteCommit.append(commits[0]['commit']['author']['name'])
  remoteCommit.append(commits[0]['commit']['author']['email'])
  remoteCommit.append(commits[0]['commit']['author']['date'])
  remoteCommit.append(commits[0]['commit']['message'])
  print("Fetched most recent commit by %s <%s> on %s \n\tCommit message: %s\n" % (tuple(remoteCommit)))
  return remoteCommit

def load_config():
  global user
  global paths
  with open(config, 'r') as f:
    loadedConfig = json.load(f)
  user = loadedConfig[0]['git']
  paths = loadedConfig[0]['repos']

def load_repo(path):
  global user
  local = local_status(paths[path])
  print("\tRepo: ", repo)
  remote_status(user["id"], repo)
  print(local.active_branch.name)

global user
global paths
user = []
paths = []
config = 'gitloaded.json'

# Load user JSON config
load_config()
print("Loaded user: %s\n" % user)
print("Loaded paths: %s\n" % paths)

for repo in paths:
  print("Loading path: %s" % paths[repo])
  load_repo(repo)
  print()

