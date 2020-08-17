from restaurant import Restaurant

class IceCreamParlor(Restaurant):
    def __init__(self, name, cuisine_type, base_price, extra_size, extra_scoop, *flavors):
        super().__init__(name, cuisine_type)
        self.flavors = []
        self.base_price = base_price
        self.extra_size = extra_size
        self.extra_scoop = extra_scoop
        self.sizes = {"Small" : self.base_price, "Medium" : self.base_price + self.extra_size, "Large" : self.base_price + (self.extra_size * 2)}
    def get_stored_flavors(self, *flavors):
        filename = "flavors.txt"
        with open(filename, "r") as file:
            self.flavors = file.read().split(",")
        return self.flavors
    def update_flavors(self, *flavors):
        self.get_stored_flavors(self, *flavors)
        while True:
            flavors = (input("Which flavor? ")).title()
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
    def customer_ticket(self, *flavors):
        self.get_stored_flavors(self, *flavors)
        customer_flavor = input("Which flavor would you like? ").title()
        customer_size = input("Which size cone would you like? ").title()
        extra_query = input("Would you like an extra scoop? ").lower()
        for flavor in self.flavors:
            for size in self.sizes:
                if customer_flavor == flavor and customer_size == size:
                    if extra_query == "yes":
                        self.sizes[customer_size] = (int(self.sizes[customer_size]) + self.extra_scoop)
                    print(f"\nThat'll be ${self.sizes[customer_size]:0.2f}!")
                    print(f"\nHere's Your {customer_size}, {customer_flavor} Cone!\n")