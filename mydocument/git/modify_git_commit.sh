#! /bin/bash

# 具体参考https://segmentfault.com/a/1190000008032330

# 一般修改最后一次commit直接使用
# git commit --amend


# 修改多次commit
git filter-branch -f --env-filter '
OLD_EMAIL="111@qq.com"
CORRECT_NAME="lotluck"
CORRECT_EMAIL="222@qq.com"
if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" ]
then
		    export GIT_COMMITTER_NAME="$CORRECT_NAME"
					    export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" ]
then
		    export GIT_AUTHOR_NAME="$CORRECT_NAME"
					    export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags


git push --force --tags origin 'refs/heads/*'




