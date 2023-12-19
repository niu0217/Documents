# Python命名规则

## 建议的命名方式

| 类型              | 公有       | 内部                       |
| ----------------- | ---------- | -------------------------- |
| 包                | 小写下划线 |                            |
| 模块              | 小写下划线 | 下划线+小写下划线          |
| 类                | 大驼峰     | 下划线+大驼峰              |
| 异常              | 大驼峰     |                            |
| 函数              | 小写下划线 | 下划线+小写下划线          |
| 全局常量/类常量   | 大写下划线 | 下划线+大写下划线          |
| 全局变量/类变量   | 小写下划线 | 下划线+小写下划线          |
| 实例变量          | 小写下划线 | 下划线+小写下划线 (受保护) |
| 方法名            | 小写下划线 | 下划线+小写下划线 (受保护) |
| 函数参数/方法参数 | 小写下划线 |                            |
| 局部变量          | 小写下划线 |                            |

| 类型              | 公有                 | 内部                  |
| ----------------- | -------------------- | --------------------- |
| 包                | `lower_with_under`   |                       |
| 模块              | `lower_with_under`   | `_lower_with_under`   |
| 类                | `CapWords`           | `_CapWords`           |
| 异常              | `CapWords`           |                       |
| 函数              | `lower_with_under()` | `_lower_with_under()` |
| 全局常量/类常量   | `CAPS_WITH_UNDER`    | `_CAPS_WITH_UNDER`    |
| 全局变量/类变量   | `lower_with_under`   | `_lower_with_under`   |
| 实例变量          | `lower_with_under`   | `_lower_with_under`   |
| 方法名            | `lower_with_under()` | `_lower_with_under()` |
| 函数参数/方法参数 | `lower_with_under`   |                       |
| 局部变量          | `lower_with_under`   |                       |

## 我的命名方式

统一使用`snake_case`命名方法。

### 变量命名

```python
# 命名规则：使用小写字母和下划线（snake_case）命名变量

# 示例1：定义和使用具有描述性名称的变量
student_name = "Alice"
student_age = 20
course_name = "Python Programming"

print(f"Student name: {student_name}")
print(f"Student age: {student_age}")
print(f"Course name: {course_name}")

# 示例2：避免使用Python关键字作为变量名
# （例如，不能使用 'for'、'while'、'if' 等作为变量名）
not_a_keyword = "This is a valid variable name."

# 示例3：使用有意义的变量名
# （例如，使用 'area_of_circle' 而不是简单的 'a'）
radius = 5
area_of_circle = 3.14 * radius ** 2

print(f"Area of circle with radius {radius}: {area_of_circle}")

# 示例4：常量通常全大写，单词间用下划线连接
PI = 3.14159
MAX_STUDENTS_PER_CLASS = 30

print(f"Value of PI: {PI}")
print(f"Max students per class: {MAX_STUDENTS_PER_CLASS}")
```

### 类型相关的命名

对于特定类型的变量，考虑在其名称中体现类型信息，如：

- 元组（Tuple）类型变量：`user_details_tuple`
- 列表（List）类型变量：`user_names_list`
- 字典（Dictionary）类型变量：`user_info_dict`
- 集合（Set）类型变量：`unique_numbers_set`

```python
# 命名规则：在变量名中包含类型信息，使用小写字母和下划线（snake_case）命名变量

# 示例1：列表类型的变量
student_names_list = ["Alice", "Bob", "Charlie"]

# 示例2：元组类型的变量
coordinates_tuple = (40.7128, -74.0060)  # 纽约市的经纬度

# 示例3：字典类型的变量
user_info_dict = {
    "name": "Alice",
    "age": 25,
    "email": "alice@example.com"
}

# 示例4：集合类型的变量
unique_numbers_set = {1, 2, 3, 4, 5}

# 示例5：自定义对象类型的变量
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

person_object = Person("Alice", 25)

# 示例6：函数返回值类型的变量
def get_temperature():
    return 20.5

temperature_float = get_temperature()

print(f"Student names: {student_names_list}")
print(f"Coordinates: {coordinates_tuple}")
print(f"User info: {user_info_dict}")
print(f"Unique numbers: {unique_numbers_set}")
print(f"Person object: {person_object.name}, {person_object.age}")
print(f"Temperature: {temperature_float}")
```

### 类

```python
class Employee:
    def __init__(self, name, age, salary):
        # 公有变量
        self.name = name
        self.age = age

        # 私有变量，名称改编后为 _Employee__salary
        self.__salary = salary

    # 公有方法
    def introduce(self):
        print(f"Hi, my name is {self.name}, I am {self.age} years old.")

    # 私有方法，名称改编后为 _Employee__increase_salary
    def __increase_salary(self, percentage):
        self.__salary *= (1 + percentage / 100)

    # 受保护的方法，使用单下划线前缀表示
    def _apply_bonus(self, bonus_amount):
        self.__salary += bonus_amount

    # 公开的getter方法来获取私有变量的值
    def get_salary(self):
        return self.__salary

# 创建一个 Employee 的实例
emp = Employee("John Doe", 30, 50000)

# 访问和修改公有变量
print(emp.name)  # 输出: John Doe
emp.age = 31
print(emp.age)  # 输出: 31

# 调用公有方法
emp.introduce()  # 输出: Hi, my name is John Doe, I am 31 years old.

# 尝试直接访问私有变量，这将引发 AttributeError
try:
    print(emp.__salary)
except AttributeError as e:
    print(e)  # 输出: 'Employee' object has no attribute '__salary'

# 尝试直接调用私有方法，这将引发 AttributeError
try:
    emp.__increase_salary(5)
except AttributeError as e:
    print(e)  # 输出: 'Employee' object has no attribute '__increase_salary'

# 通过公共方法访问私有变量
print(emp.get_salary())  # 输出: 50000

# 调用受保护的方法
emp._apply_bonus(1000)
print(emp.get_salary())  # 输出: 51000
```

```python
# 命名规则：使用驼峰命名法（PascalCase）命名类

class Animal:
    def __init__(self, name, species):
        # 实例变量（属性）
        self.name = name
        self.species = species

    def speak(self):
        raise NotImplementedError("Subclass must implement the 'speak' method.")


class Dog(Animal):
    def speak(self):
        return f"{self.name} says Woof!"


class Cat(Animal):
    def speak(self):
        return f"{self.name} says Meow!"


def introduce_animals(animals):
    for animal in animals:
        print(f"{animal.name} is a {animal.species}.")
        print(animal.speak())


if __name__ == "__main__":
    # 创建动物实例
    dog1 = Dog("Rex", "Dog")
    cat1 = Cat("Whiskers", "Cat")

    # 定义一个动物列表
    animals = [dog1, cat1]

    # 介绍动物
    introduce_animals(animals)
```

