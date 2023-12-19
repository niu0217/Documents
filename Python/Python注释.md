# Python注释

## 函数

```python
def calculate_average(numbers):
    """
    Calculate the average of a list of numbers.

    Args:
        numbers (list[float]): A list of numbers.

    Returns:
        float: The average of the numbers in the list.
    """

    # Calculate the sum of the numbers
    total = sum(numbers)

    # Calculate the length of the numbers list
    length = len(numbers)

    # Calculate and return the average
    average = total / length
    return average


if __name__ == "__main__":
    # Test the function
    number_list = [1, 2, 3, 4, 5]
    result = calculate_average(number_list)
    print(f"The average of the number list {number_list} is: {result}")
```

## 类

```python
class Student:
    """
    A class representing a student with attributes such as name, age, and grade.

    Attributes:
        name (str): The name of the student.
        age (int): The age of the student.
        grade (float): The grade point average of the student.

    Methods:
        __init__: Initialize the Student object with name, age, and grade.
        introduce: Print a brief introduction of the student.
    """

    def __init__(self, name, age, grade):
        """
        Initialize the Student object with name, age, and grade.

        Args:
            name (str): The name of the student.
            age (int): The age of the student.
            grade (float): The grade point average of the student.
        """
        self.name = name
        self.age = age
        self.grade = grade

    def introduce(self):
        """
        Print a brief introduction of the student.

        Returns:
            None
        """
        print(f"Hi, my name is {self.name}, I am {self.age} years old, and my GPA is {self.grade}.")


if __name__ == "__main__":
    # Create a Student object and introduce the student
    student = Student("Alice", 18, 3.5)
    student.introduce()
```

## 文件

```python
#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
student_management.py

这是一个用于管理学生信息的模块。

该模块包含以下功能：
1. 定义一个表示学生的类（Student）
2. 提供添加、删除和查询学生信息的功能

Author: Your Name
Date: 2023-03-01
"""

from datetime import datetime


class Student:
    """
    A class representing a student with attributes such as name, age, and grade.

    Attributes:
        name (str): The name of the student.
        age (int): The age of the student.
        grade (float): The grade point average of the student.
        enrollment_date (datetime): The date when the student enrolled.

    Methods:
        __init__: Initialize the Student object with name, age, and grade.
        introduce: Print a brief introduction of the student.
    """

    def __init__(self, name, age, grade):
        """
        Initialize the Student object with name, age, and grade.

        Args:
            name (str): The name of the student.
            age (int): The age of the student.
            grade (float): The grade point average of the student.
        """
        self.name = name
        self.age = age
        self.grade = grade
        self.enrollment_date = datetime.now()

    def introduce(self):
        """
        Print a brief introduction of the student.

        Returns:
            None
        """
        print(f"Hi, my name is {self.name}, I am {self.age} years old, "
              f"my GPA is {self.grade}, and I enrolled on {self.enrollment_date}.")


def add_student(name, age, grade):
    """
    Add a new student to the system.

    Args:
        name (str): The name of the student.
        age (int): The age of the student.
        grade (float): The grade point average of the student.

    Returns:
        Student: The created Student object.
    """
    student = Student(name, age, grade)
    # Add the student to the system (e.g., database or data structure)
    return student


def remove_student(student):
    """
    Remove a student from the system.

    Args:
        student (Student): The student to be removed.

    Returns:
        bool: True if the student was successfully removed, False otherwise.
    """
    # Remove the student from the system (e.g., database or data structure)
    return True


def find_student_by_name(name):
    """
    Find a student by their name.

    Args:
        name (str): The name of the student.

    Returns:
        Student or None: The found Student object or None if not found.
    """
    # Search for the student in the system (e.g., database or data structure)
    return None


if __name__ == "__main__":
    # Test the module functions
    student = add_student("Alice", 18, 3.5)
    student.introduce()
```

