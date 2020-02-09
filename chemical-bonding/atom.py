import numpy as np

class Atom:
	# (symbol = atomic symbol, number = atomic number in periodic table, relative atomic mass, ve = valence electrons)
	def __init__(self, atomic_name, symbol, number, relative_atomic_mass, energy_levels):
		self.atomic_name = atomic_name
		self.symbol = symbol # character
		self.atomic_number = number
		self.relative_atomic_mass = relative_atomic_mass
		self.protons = number
		self.relative_atomic_mass = relative_atomic_mass
		self.neutrons = None
		self.electrons = number
		self.energy_levels = energy_levels
		self.ionic_charge = 0
		# compute the amount of neutrons in the atom based on its
		# relative atomic mass value (protons + neutrons)
		relative_atomic_mass_decimal = relative_atomic_mass - int(relative_atomic_mass)
		# round up the relative atomic mass 
		if relative_atomic_mass_decimal >= 0.5:
			self.neutrons = (int(relative_atomic_mass) + 1) - self.protons
		else:
			self.neutrons = int(relative_atomic_mass) - self.protons
		# since the energy level and the amount of electrons are specified, 
		# we can compute the amount of valence electrons of the atom
		electron = 2
		orbital_shift = 1
		sum = 0
		self.electron_shell = np.zeros(self.energy_levels)
		for level in range(1, self.energy_levels + 1):
			if level % 2 != 0:
				pass
			else:
				if level == 2:
					electron = 2 * (level ** 2)
				else:
					electron = 2 * ((level - orbital_shift) ** 2)
					orbital_shift += 1
			# if the it reached the outer energy level
			if level == self.energy_levels:
				self.electron_shell[level - 1] = self.electrons - sum
			else:
				self.electron_shell[level - 1] = electron
			sum += electron
	def compute_ionic_charge(self):
		if (self.electron_shell[self.energy_levels - 1] >= 1) and (self.electron_shell[self.energy_levels - 1] <= 4):
			self.ionic_charge = self.electron_shell[self.energy_levels - 1]
		else:
			self.ionic_charge = self.electron_shell[self.energy_levels - 1] - 8
		return self.ionic_charge
	def atomic_symbol(self):
		return self.symbol
	def name(self):
		return self.atomic_name
	def show_atomic_information(self):
		print('Atomic Name = {0}' .format(self.atomic_name))
		print('Symbol = {0}' .format(self.symbol))
		print('Atomic Number = {0}' .format(self.atomic_number))
		print('Relative Atomic Mass = {0}' .format(self.relative_atomic_mass))
		print('Protons = {0}' .format(self.protons))
		print('Relative Neutrons = {0}' .format(self.neutrons))
		print('Electrons = {0}' .format(self.electrons))
		print('Valence Electrons = {0}\n' .format(self.electron_shell[self.energy_levels - 1]))