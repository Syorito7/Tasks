import requests
from bs4 import BeautifulSoup

def get_leetcode_profile(username):
    url = f"https://leetcode.com/{username}/"
    response = requests.get(url)
    
    if response.status_code != 200:
        raise Exception(f"Failed to fetch profile data for user {username}")
    
    soup = BeautifulSoup(response.text, 'html.parser')
    
    profile_data = {
        'username': username,
        'ranking': soup.find('div', class_='rank').text.strip() if soup.find('div', class_='rank') else 'N/A',
        'total_solved': soup.find('div', class_='total-solved-count').text.strip() if soup.find('div', class_='total-solved-count') else 'N/A',
        'easy_solved': soup.find('div', class_='easy-solved-count').text.strip() if soup.find('div', class_='easy-solved-count') else 'N/A',
        'medium_solved': soup.find('div', class_='medium-solved-count').text.strip() if soup.find('div', class_='medium-solved-count') else 'N/A',
        'hard_solved': soup.find('div', class_='hard-solved-count').text.strip() if soup.find('div', class_='hard-solved-count') else 'N/A'
    }
    
    return profile_data

def update_readme(profile_data):
    with open('README.md', 'r') as file:
        readme_content = file.readlines()
    
    new_content = []
    in_profile_section = False
    
    for line in readme_content:
        if line.strip() == "<!-- LEETCODE_PROFILE_START -->":
            in_profile_section = True
            new_content.append(line)
            new_content.append(f"### LeetCode Profile: [{profile_data['username']}](https://leetcode.com/{profile_data['username']}/)\n")
            new_content.append(f"- **Ranking:** {profile_data['ranking']}\n")
            new_content.append(f"- **Total Problems Solved:** {profile_data['total_solved']}\n")
            new_content.append(f"- **Easy Problems Solved:** {profile_data['easy_solved']}\n")
            new_content.append(f"- **Medium Problems Solved:** {profile_data['medium_solved']}\n")
            new_content.append(f"- **Hard Problems Solved:** {profile_data['hard_solved']}\n")
        elif line.strip() == "<!-- LEETCODE_PROFILE_END -->":
            in_profile_section = False
        
        if not in_profile_section:
            new_content.append(line)
    
    with open('README.md', 'w') as file:
        file.writelines(new_content)

if __name__ == "__main__":
    username = "syorito7"
    profile_data = get_leetcode_profile(username)
    update_readme(profile_data)
    
    with open('README.md', 'r') as file:
        print(file.read())
