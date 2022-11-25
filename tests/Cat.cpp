/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:40:17 by mamuller          #+#    #+#             */
/*   Updated: 2022/04/22 12:40:17 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat()
{
	type = "Cat";
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_YELLOW << "Cat"  << COLOR_DEFAULT << " default constructor called" << std::endl;
	brain = new Brain();
}

Cat::Cat(const Cat& obj):AAnimal()
{
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_YELLOW << "Cat" << COLOR_DEFAULT << " copy constructor called" << std::endl;
	this->type = obj.type;
	brain = new Brain(*(obj.brain));
}

Cat::~Cat()
{
	delete(brain);
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_YELLOW << "Cat" << COLOR_DEFAULT << " destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& rhs)
{
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_YELLOW << "Cat" << COLOR_DEFAULT << " copy assignment operator called" << std::endl;
	*(this->brain) = *(rhs.brain);
	this->type = rhs.type;
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << COLOR_GREY << "Meow, Meow" << COLOR_DEFAULT << std::endl;
}

Brain* Cat::getBrain() const
{
	return (this->brain);
}
