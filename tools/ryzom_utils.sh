#!/bin/bash

function check_repository {
	cd $1
	BRANCH=$(hg branch)
	clr_green "Getting remote repository version..."
	REPO_PATH=$(hg paths default)
	REMOTE=$(hg id $REPO_PATH#$BRANCH | cut -d" " -f1)
	LOCAL=$(hg id | cut -d" " -f1)

	color "orange" "$REPO_PATH [$BRANCH] at $1: "
	if [ "$LOCAL" == "$REMOTE" ] || [ "$LOCAL" == "$REMOTE+" ]
	then
		clr_cyan "Latest version!"
	else
		clr_red "Outdated version..."
		ask "Repository is not up to date. Do you want update it?"
		select_list "No:No" "$2:Yes, update repository"
	fi
}
