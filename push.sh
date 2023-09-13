git add .
read -r -p "Your commit message: " message
git commit -m "$message"
git remote add origin https://learn.zone01dakar.sn/git/pba/atm-management-system.git
git push