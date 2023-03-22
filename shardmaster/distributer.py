import heapq

class MinHeap:
    def __init__(self, arr):
        self.arr = arr
        heapq.heapify(self.arr)
    
    def push(self, item):
        heapq.heappush(self.arr, item)
    
    def pop(self):
        return heapq.heappop(self.arr)
    
    def peek(self):
        return self.arr[0]
    
    def empty(self):
        return len(self.arr) == 0

class MaxHeap:
    def __init__(self, arr):
        self.arr = arr
        for(i, item) in enumerate(self.arr):
            self.arr[i] = (-item[0], item[1])
        heapq.heapify(self.arr)
    
    def push(self, item):
        heapq.heappush(self.arr, (-item[0], item[1]))
    
    def pop(self):
        (shard_count, group_id) = heapq.heappop(self.arr)
        return (-shard_count, group_id)
    
    def peek(self):
        _peek = self.arr[0]
        return (-_peek[0], _peek[1])
    
    def empty(self):
        return len(self.arr) == 0

class Distributer:

    def __init__(self, shard_count):
        # a map from groupd_id to a list of shard_ids
        self.config = {}
        self.shard_count = shard_count
        self.groups = set()
    
    def add(self, group_id):
        self.groups.add(group_id)
        self.update(group_id, True)

    def remove(self, group_id):
        self.groups.remove(group_id)
        self.update(group_id, False)
    
    def get_config(self):
        return self.config
    
    def print_configs(self):
        print(f"config: {self.config}\n")

    def fromMapToArr(self, filter = []):
        arr = []
        for group_id in self.groups:
            if group_id not in filter:
                arr.append((len(self.config[group_id]), group_id))
        return arr

    def update(self, related_group_id, from_add):
        print(f"update group_id: {related_group_id}, from_add: {from_add}")
        print(f"current config: {self.config}")
        if from_add:
            responable_shards = []
            seize_shard_count = self.shard_count // len(self.groups)
            max_heap = MaxHeap(self.fromMapToArr([related_group_id]))
            if max_heap.empty():
                self.config[related_group_id] = [i+1 for i in range(self.shard_count)]
            else:
                # Try to seize the shards from the group with the most shards
                while seize_shard_count > 0:
                    (shard_count, group_id) = max_heap.pop()
                    sized_shard = self.config[group_id].pop()
                    responable_shards.append(sized_shard)
                    seize_shard_count -= 1
                    max_heap.push((shard_count - 1, group_id))
                self.config[related_group_id] = responable_shards

        else:
            tuples = self.fromMapToArr([related_group_id])
            print(f"tuples: {tuples}")
            min_heap = MinHeap(tuples)
            if min_heap.empty():
                # delete the key
                del self.config[related_group_id]
            else:
                # Try to distribute the shards to the group with the least shards
                shard_num = len(self.config[related_group_id])
                related_shards = self.config[related_group_id]
                while shard_num > 0:
                    (shard_count, group_id) = min_heap.pop()
                    sized_shard = related_shards.pop()
                    self.config[group_id].append(sized_shard)
                    shard_num -= 1
                    min_heap.push((shard_count, group_id))
                del self.config[related_group_id]

    

# main function
shard_count = 10
distributer = Distributer(shard_count)
distributer.add(1)
distributer.print_configs()
distributer.add(2)
distributer.print_configs()

distributer.remove(1)
distributer.print_configs()

distributer.add(3)
distributer.print_configs()

distributer.remove(2)
distributer.print_configs()
distributer.add(1)
distributer.print_configs()
distributer.add(2)
distributer.print_configs()
distributer.add(4)
distributer.print_configs()