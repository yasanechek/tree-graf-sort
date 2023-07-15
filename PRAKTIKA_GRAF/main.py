from __future__ import annotations


class MyGraph:
    adjacency_matrix = {}

    my_paths = []

    def __init__(self, matrix=None):
        self.my_paths = []
        if matrix is None:
            self.adjacency_matrix = {}
        else:
            self.adjacency_matrix = matrix

    def getWeight(self, v, w):
        return self.adjacency_matrix[v][self.__v_index(w)]

    def __check_top(self, v: str | int) -> str | int:
        tops = list(self.adjacency_matrix.keys())
        if isinstance(v, int):
            if v > len(tops):
                return -1
            return tops[v - 1]
        else:
            return v.upper()

    def __v_index(self, v: str) -> int:
        for i, top in enumerate(self.adjacency_matrix.keys()):
            if top == v:
                return i

    def first(self, v: str | int) -> int:
        top = self.__check_top(v)
        if top == -1:
            print('Вершины с таким индексом не существует')
            return 0
        if top in self.adjacency_matrix.keys():
            for i, weight in enumerate(self.adjacency_matrix.get(top), start=1):
                if weight > 0:
                    return i
        else:
            print(f'Вершины с названием {top} не существует')
        return 0

    def next(self, v: str | int, i: int) -> int:
        top = self.__check_top(v)
        if top == -1:
            print('Вершины с таким индексом не существует')
            return -1
        if i > len(list(self.adjacency_matrix.keys())):
            print('Превышено количество вершин')
            return -1
        if top in self.adjacency_matrix.keys():
            for i, weight in enumerate(self.adjacency_matrix.get(top)[i:], start=i + 1):
                if weight > 0:
                    return i
        else:
            print(f'Вершины с названием {top} не существует')
        return -1

    def vertex(self, v: str | int, i: int) -> int|None:
        top = self.__check_top(v)
        if top == -1:
            print(f'Вершины с индексом {v} не существует')
            return
        if top not in self.adjacency_matrix.keys():
            print( f'Вершины с названием {top} не существует')
            return
        if i > len(list(self.adjacency_matrix.keys())):
            print( f'Вершины с индексом {i} не существует')
            return

        return i

    def add_v(self, v_name: str, marks: list[int] = None) -> None:
        if v_name in self.adjacency_matrix.keys():
            print(f'Вершина с названием {v_name} уже существует')
            return
        if marks is None:
            for i, key in enumerate(self.adjacency_matrix.keys()):
                self.adjacency_matrix[key].append(0)
            self.adjacency_matrix[v_name] = [0] * (len(self.adjacency_matrix) + 1)
            return
        if isinstance(marks, list) and len(marks) == len(self.adjacency_matrix.keys()) + 1 \
                and all(map(lambda x: str(x).isdigit() and x >= 0, marks)):
            for i, key in enumerate(self.adjacency_matrix.keys()):
                self.adjacency_matrix[key].append(marks[i])
            self.adjacency_matrix[v_name] = marks

        else:
            print(f'Ошибка маркировки! Пример: [0, 2, 4, 5, 0]')
            return

    def add_e(self, v: int | str, w: int | str, c: int) -> None:
        top1 = self.__check_top(v)
        top2 = self.__check_top(w)
        if top1 == top2:
            print("Нельзя описать дугу одной вершины")
            return
        if top1 == -1:
            print(f'Вершины с индексом {v} не существует')
            return
        if top2 == -1:
            print(f'Вершины с индексом {w} не существует')
            return
        if top1 not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top1} не существует')
            return
        if top2 not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top2} не существует')
            return
        if self.adjacency_matrix[top1][self.__v_index(top2)] != 0:
            print('Данная дуга уже существует')
            return
        self.adjacency_matrix[top1][self.__v_index(top2)] = c

    def del_v(self, v_name: str | int) -> None:
        top = self.__check_top(v_name)
        if top == -1:
            print(f'Вершины с индексом {v_name} не существует')
            return
        if top not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top} не существует')
            return
        i = self.__v_index(top)
        self.adjacency_matrix.pop(top)
        for key in self.adjacency_matrix.keys():
            self.adjacency_matrix[key].pop(i)

    def del_e(self, v: int | str, w: int | str) -> None:
        top1 = self.__check_top(v)
        top2 = self.__check_top(w)
        if top1 == top2:
            print("Нельзя описать дугу одной вершины")
            return
        if top1 == -1:
            print(f'Вершины с индексом {v} не существует')
            return
        if top2 == -1:
            print(f'Вершины с индексом {w} не существует')
            return
        if top1 not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top1} не существует')
            return
        if top2 not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top2} не существует')
            return
        self.adjacency_matrix[top1][self.__v_index(top2)] = 0

    def edit_v(self, v_name: str, marks: list[int] = None) -> None:
        if v_name.upper() not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {v_name} не существует')
            return
        if marks is None:
            self.adjacency_matrix[v_name] = [0] * len(self.adjacency_matrix)
            return
        if isinstance(marks, list) and len(marks) == len(self.adjacency_matrix.keys()) \
                and all(map(lambda x: str(x).isdigit() and x >= 0, marks)):
            for i, key in enumerate(self.adjacency_matrix.keys()):
                self.adjacency_matrix[key][i] = marks[i]
            self.adjacency_matrix[v_name] = marks
        else:
            print(f'Ошибка маркировки! Пример: [0, 2, 4, 5, 0]')
            return

    def edit_e(self, v: int | str, w: int | str, c: int) -> None:
        top1 = self.__check_top(v)
        top2 = self.__check_top(w)
        if top1 == top2:
            print("Нельзя описать дугу одной вершины")
            return
        if top1 == -1:
            print(f'Вершины с индексом {v} не существует')
            return
        if top2 == -1:
            print(f'Вершины с индексом {w} не существует')
            return
        if top1 not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top1} не существует')
            return
        if top2 not in self.adjacency_matrix.keys():
            print(f'Вершины с названием {top2} не существует')
            return
        self.adjacency_matrix[top1][self.__v_index(top2)] = c

    def show(self) -> None:
        [print(m) for m in self.adjacency_matrix.values()]

    def printAllPaths(self, start_v, end_v, visited, path):

        visited[list(self.adjacency_matrix.keys()).index(start_v)] = True
        path.append(start_v)

        if start_v == end_v:
            if tuple(path) not in self.my_paths:
                self.my_paths.append(tuple(path))

        else:
            for i in range(len(self.adjacency_matrix.keys())):
                v = self.next(start_v, i)
                if v == -1:
                    continue
                top = self.__check_top(v)
                if not visited[list(self.adjacency_matrix.keys()).index(top)]:
                    self.printAllPaths(top, end_v, visited, path)
        path.pop()
        visited[list(self.adjacency_matrix.keys()).index(start_v)] = False

    def allPaths(self, s, d):

        visited = [False] * len(self.adjacency_matrix.keys())

        path = []

        self.printAllPaths(s, d, visited, path)

    def task(self):
        w = int(input(('Введите вес путей: ')))
        for top1 in self.adjacency_matrix.keys():
            for top2 in self.adjacency_matrix.keys():
                self.allPaths(top1, top2)
        for path in self.my_paths:
            weight_path = 0
            for i in range(len(path) - 1):
                weight_path += self.getWeight(path[i], path[i + 1])
            if weight_path == w:
                print(path)



if __name__ == '__main__':
    print("Первый пример:")
    # a = MyGraph()
    # # Пример №1
    # a.add_v('A')
    # a.add_v('B')
    # a.add_v('C')
    # a.add_v('D')
    # a.add_v('E')
    # a.add_e('A', 'B', 2)
    # a.add_e('B', 'A', 4)
    # a.add_e('B', 'E', 3)
    # a.add_e('B', 'C', 5)
    # a.add_e('D', 'B', 11)
    # a.add_e('D', 'E', 13)
    # a.add_e('E', 'C', 7)
    # a.task()

    print("Второй пример:")
    b = MyGraph()
    # Пример №2
    b.add_v('A')
    b.add_v('B')
    b.add_v('C')
    b.add_v('D')
    b.add_e('A', 'B', 3)
    b.add_e('B', 'D', 10)
    b.add_e('D', 'A', 11)
    b.add_e('C', 'B', 4)
    b.add_e('C', 'D', 8)
    b.task()
