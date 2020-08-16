from restaurant import Restaurant

class IceCreamStand(Restaurant):
    def __init__(self, name, cuisine_type, *flavors):
	    super().__init__(name, cuisine_type)
	    self.flavors = []
    def get_stored_flavors(self, *flavors):
        filename = "flavors.txt"
        with open(filename, "r") as file:
            self.flavors = file.read().split(",")
        return self.flavors
    def update_flavors(self, *flavors):
        self.get_stored_flavors(self, *flavors)
        while True:
            flavors = (input("New flavor?")).title()
            if flavors != "Q" and flavors not in self.flavors:
                self.flavors.append(flavors)
            if flavors in self.flavors:
                continue
            else:
                break
        filename = "flavors.txt"
        with open(filename, "w") as file:
            new_flavors = ",".join(map(str, self.flavors))
            file.write(new_flavors)
    def describe_flavors(self, *flavors):
        menu = self.get_stored_flavors(*flavors)
        menu = ", ".join(map(str, menu))[2:]
        print(f"{self.name} serves {menu}.")