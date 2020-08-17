import copy, csv

class Restaurant:
    def __init__(self, name, cuisine_type):
        self.name = name
        self.cuisine_type = cuisine_type
        self.item = {"order" : None, "taste" : None, "price" : 0.00, "avail" : 0, "service" : None, "allergy" : False}
        self.menu = []
    def describe_restaurant(self):
        print(f"{self.name} serves {self.cuisine_type}.")
    def open_restaurant(self):
        print(f"{self.name} is open for business in accordance with COVID-19 guidelines.")
    def load_menu(self):
        with open("menu.csv", "r") as file:
            fieldnames = ["order", "taste", "price", "avail", "service", "allergy"]
            self.menu = [{key: value for key, value in row.items()} for row in csv.DictReader(file, fieldnames=fieldnames)]
        return self.menu
    def write_menu(self):
        with open("menu.csv", "w", encoding="utf8", newline="") as file:
            fieldnames = ["order", "taste", "price", "avail", "service", "allergy"]
            writer = csv.DictWriter(file, fieldnames=fieldnames)
            writer.writerows(self.menu)
    def update_menu(self):
        self.load_menu()
        while True:
            order = input("What's new on the menu today? ").title()
            if order not in self.item.values():
                self.item["order"] = order
            else:
                continue
            self.item["taste"] = input(str("Describe the item in a sentence or two. "))
            price = float(input("What's the market price? "))
            if price >= 0.00:
                self.item["price"] = price
            avail = int(input("How many orders can we serve today? "))
            if avail >= 0:
                self.item["avail"] = avail
            service = input("For which service: breakfast, lunch, appetizer, entree, dessert, cafe, or bar? ").lower()
            if service in ("breakfast", "lunch", "appetizer", "entree", "dessert", "cafe", "bar"):
                self.item["service"] = service
            allergy = input("Are there high-risk allergies associated with this item? ").lower()
            if allergy == "yes":
                self.item["allergy"] = True
            self.menu.append(copy.deepcopy(self.item))
            prompt = input("Any more additions to the menu? ").lower()
            if prompt != "yes":
                break
        self.write_menu()
        return self.menu
    def print_menu(self):
        self.load_menu()
        menu_query = input("Which menu: breakfast, lunch, appetizer, entree, dessert, cafe, bar -- or the full menu? ").lower()
        service_menu = [self.item for self.item in self.menu if menu_query in self.item["service"] or menu_query == "full"]
        for self.item in service_menu:
            print(f'\n\t{self.item["order"]}, {self.item["taste"]}, {self.item["price"]}')
    def take_stock(self):
        self.load_menu()
        supply_query = int(input("What's the maximum stock for current inventory you want to review? "))
        low_supply = [self.item for self.item in self.menu if int(self.item["avail"]) <= supply_query]
        print(low_supply)
    def decrement_stock(self):
        self.item["avail"] = (int(self.item["avail"]) - 1)
        self.write_menu()
        return self.menu
    def restock(self):
        self.load_menu()
        stock = input("What are we restocking? ").title()
        restock = int(input("How much stock have we replenished? "))
        for self.item in self.menu:
            if stock in self.item["order"]:
                self.item["avail"] = (int(self.item["avail"]) + restock)
                self.write_menu()
    def customer_order(self):
        self.load_menu()
        self.print_menu()
        customer_allergy = input("Do you have any allergies? ").lower()
        while True:
            order = input("What would you like to order? ").title()
            if order == "Q":
                break
            for self.item in self.menu:
                if order in self.item["order"]:
                    if customer_allergy == "yes" and self.item["allergy"] == "True":
                        print("I'm sorry but you appear to be allergic.")
                    elif int(self.item["avail"]) > 0:
                        self.decrement_stock()
                        print("We'll have that right out to you.")
                    else:
                        print("I'm sorry but we're out of that right now.")