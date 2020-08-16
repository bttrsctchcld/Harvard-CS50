from restaurant import *
from parlor import *

my_restaurant = Restaurant("Lovelace Diner", "American")
my_restaurant.describe_restaurant()
my_restaurant.open_restaurant()
my_restaurant.print_menu()
my_parlor = IceCreamParlor("Kanamori's", "ice cream")
my_parlor.describe_restaurant()
my_parlor.describe_flavors()