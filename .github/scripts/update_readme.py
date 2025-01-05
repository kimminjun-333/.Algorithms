import os
import requests
from datetime import datetime
from typing import Dict, List
import json

class ProblemInfo:
    def __init__(self, number: str, data: Dict):
        self.number = number
        self.title = data.get('titleKo', '')
        self.level = data.get('level', 0)
        self.tags = [tag['key'] for tag in data.get('tags', [])]
        
    def get_difficulty_emoji(self) -> str:
        # solved.ac 레벨에 따른 이모지 반환
        level_emoji = {
            0: '🌱',  # Unrated
            1: '🥉', 2: '🥉', 3: '🥉', 4: '🥉', 5: '🥉',  # Bronze
            6: '🥈', 7: '🥈', 8: '🥈', 9: '🥈', 10: '🥈',  # Silver
            11: '🥇', 12: '🥇', 13: '🥇', 14: '🥇', 15: '🥇',  # Gold
            16: '💎', 17: '💎', 18: '💎', 19: '💎', 20: '💎',  # Platinum
            21: '👑', 22: '👑', 23: '👑', 24: '👑', 25: '👑',  # Diamond
            26: '🏆', 27: '🏆', 28: '🏆', 29: '🏆', 30: '🏆'   # Ruby
        }
        return level_emoji.get(self.level, '🌱')

def fetch_problem_info(problem_numbers: List[str]) -> Dict[str, ProblemInfo]:
    """solved.ac API를 사용하여 문제 정보를 가져옵니다"""
    problems = {}
    
    # 100개씩 나누어 요청 (API 제한 고려)
    for i in range(0, len(problem_numbers), 100):
        batch = problem_numbers[i:i+100]
        query = ','.join(batch)
        url = f"https://solved.ac/api/v3/problem/lookup?problemIds={query}"
        
        try:
            response = requests.get(url, headers={'Content-Type': 'application/json'})
            if response.status_code == 200:
                for prob_data in response.json():
                    prob_num = str(prob_data['problemId'])
                    problems[prob_num] = ProblemInfo(prob_num, prob_data)
        except Exception as e:
            print(f"Error fetching problem info: {e}")
            continue
            
    return problems

def get_problem_sections():
    problems = {}  # 동적으로 카테고리 생성
    solutions_dir = "Solutions/Baekjoon"
    
    # 문제 번호 수집
    problem_numbers = []
    for problem_dir in os.listdir(solutions_dir):
        if problem_dir.isdigit():
            problem_numbers.append(problem_dir)
    
    # solved.ac API로 문제 정보 가져오기
    problem_info = fetch_problem_info(problem_numbers)
    
    # 문제 분류 (태그 기반)
    for problem_dir in problem_numbers:
        if problem_dir in problem_info:
            info = problem_info[problem_dir]
            problem_path = f"Solutions/Baekjoon/{problem_dir}"
            
            problem_data = {
                'number': problem_dir,
                'name': info.title,
                'path': f"{problem_path}.cpp",
                'difficulty': info.get_difficulty_emoji(),
                'tags': info.tags
            }
            
            # 각 태그별로 카테고리 생성 및 문제 추가
            for tag in info.tags:
                if tag not in problems:
                    problems[tag] = []
                problems[tag].append(problem_data)
    
    return problems

def get_current_focus():
    try:
        with open(".github/config/current_focus.json", "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception as e:
        print(f"Error loading current focus: {e}")
        return {"current_focus": []}

def update_readme():
    # 현재 README.md 파일을 읽습니다
    with open("README.md", "r", encoding="utf-8") as f:
        content = f.readlines()
    
    # 각 섹션의 시작과 끝 인덱스를 찾습니다
    sections = {
        'header': {'start': -1, 'end': -1},
        'current_status': {'start': -1, 'end': -1},
        'learning_progress': {'start': -1, 'end': -1},
        'current_focus': {'start': -1, 'end': -1},
        'problem_solving': {'start': -1, 'end': -1},
        'development_env': {'start': -1, 'end': -1},
        'references': {'start': -1, 'end': -1}
    }
    
    # 각 섹션의 시작과 끝 위치를 찾습니다
    for i, line in enumerate(content):
        if '<div align="center">' in line:
            sections['header']['start'] = i
        elif '## 📊 Current Status' in line:
            sections['current_status']['start'] = i
            sections['header']['end'] = i
        elif '## 🎯 Learning Progress' in line:
            sections['learning_progress']['start'] = i
            sections['current_status']['end'] = i
        elif '## 📚 Current Focus' in line:
            sections['current_focus']['start'] = i
            sections['learning_progress']['end'] = i
        elif '## 🏃‍♂️ Problem Solving' in line:
            sections['problem_solving']['start'] = i
            sections['current_focus']['end'] = i
        elif '## 🛠 Development Environment' in line:
            sections['development_env']['start'] = i
            sections['problem_solving']['end'] = i
        elif '## 📚 References' in line:
            sections['references']['start'] = i
            sections['development_env']['end'] = i
            
    if sections['references']['start'] != -1:
        sections['references']['end'] = len(content)
    
    # Current Focus 섹션 업데이트
    if sections['current_focus']['start'] != -1:
        focus_data = get_current_focus()
        focus_section = """## 📚 Current Focus
<p align="center">
"""
        for focus in focus_data['current_focus']:
            focus_section += f'  <a href="{focus["url"]}"><img src="https://img.shields.io/badge/{focus["name"].replace(" ", "_")}-{focus["color"]}?style=flat-square&logo=TheAlgorithms&logoColor=white"/></a>\n'
        focus_section += "</p>\n\n"
        
        # Current Focus 섹션 업데이트
        content = (
            content[:sections['current_focus']['start']] +
            [focus_section] +
            content[sections['current_focus']['end']:]
        )
    
    # Problem Solving 섹션 업데이트
    if sections['problem_solving']['start'] != -1:
        # Data Structures 섹션 생성
        problems = get_problem_sections()
        problem_section = generate_problem_solving_section(problems)
        
        # Problem Solving 섹션 업데이트
        content = (
            content[:sections['problem_solving']['start']] +
            [problem_section] +
            content[sections['problem_solving']['end']:]
        )
    
    # 파일에 쓰기
    with open("README.md", "w", encoding="utf-8") as f:
        f.writelines(content)

def generate_difficulty_stats(problems):
    # 난이도 카운트
    difficulty_count = {
        '🥉': {'name': 'Bronze', 'count': 0},
        '🥈': {'name': 'Silver', 'count': 0},
        '🥇': {'name': 'Gold', 'count': 0},
        '💎': {'name': 'Platinum', 'count': 0},
        '👑': {'name': 'Diamond', 'count': 0},
        '🏆': {'name': 'Ruby', 'count': 0}
    }
    
    for tag, prob_list in problems.items():
        for prob in prob_list:
            diff = prob['difficulty']
            if diff in difficulty_count:
                difficulty_count[diff]['count'] += 1
    
    # 통계 섹션 생성
    stats_section = "\n### 🏅 Difficulty Stats\n\n"
    stats_section += "<div align='center'>\n\n"
    
    # 각 난이도별 통계 (깔끔하게 정렬된 형태)
    for diff, data in difficulty_count.items():
        count = data['count']
        # 30자 길이로 맞춰서 정렬
        formatted_text = f"{diff} {data['name']}".ljust(30)
        stats_section += f"`{formatted_text}` `{count}`\n"
    
    total = sum(d['count'] for d in difficulty_count.values())
    stats_section += f"\n**Total Solved: {total} Problems**\n"
    stats_section += "</div>\n\n"
    
    return stats_section

def generate_problem_solving_section(problems):
    problem_section = """## 🏃‍♂️ Problem Solving"""
    
    # 난이도 통계 추가
    problem_section += generate_difficulty_stats(problems)
    
    problem_section += """<details open>
<summary>Solved Problems by Category</summary>
<div align="center">
"""
    
    # 태그별로 섹션 생성 (기존 코드와 동일)
    for tag, prob_list in sorted(problems.items()):
        tag_display = tag.replace('_', ' ').title()
        problem_section += f"\n### {tag_display}\n"
        
        sorted_problems = sorted(prob_list, key=lambda x: (x['difficulty'], x['number']))
        
        for prob in sorted_problems:
            problem_section += (
                f"{prob['difficulty']} [{prob['name']} (BOJ {prob['number']})]({prob['path']})  \n"
            )
        
        test_path = f"Solutions/DataStructures/_Tests/{tag_display.replace(' ', '')}Test"
        if os.path.exists(test_path):
            problem_section += f"✅ [{tag_display} Implementation Test]({test_path}/{tag.lower()}_test.cpp)\n"
        
        problem_section += "\n"
    
    problem_section += "</div>\n</details>\n"
    
    return problem_section

if __name__ == "__main__":
    update_readme() 