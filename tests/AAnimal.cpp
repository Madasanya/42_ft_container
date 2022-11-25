/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:34:58 by mamuller          #+#    #+#             */
/*   Updated: 2022/04/22 21:34:58 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal():type("AAnimal")
{
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_GREEN << "AAnimal" << COLOR_DEFAULT << " default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& obj)
{
	this->type = obj.type;
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_GREEN <<  "AAnimal" << COLOR_DEFAULT << " copy constructor called" << std::endl;
}

AAnimal::~AAnimal()
{
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_GREEN <<  "AAnimal" << COLOR_DEFAULT << " destructor called" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& rhs)
{
	if (COMMENTS_CANONICAL)
		std::cout << COLOR_GREEN <<  "AAnimal" << COLOR_DEFAULT << "copy assignment operator called" << std::endl;
	this->type = rhs.type;
	return (*this);
}


const std::string& AAnimal::getType() const
{
	return (type);
}
