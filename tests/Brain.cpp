/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:26:03 by mamuller          #+#    #+#             */
/*   Updated: 2022/04/22 16:26:03 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	for(int i = 0; i < (int)brainSize; i++)
		ideas[i] = "Beautiful void everywhere";
	if (COMMENTS_CANONICAL)
		std::cout <<COLOR_PINK << "Brain" << COLOR_DEFAULT << " default constructor called" << std::endl;
}

Brain::Brain(const Brain& obj)
{
	std::copy(obj.ideas, obj.ideas + brainSize, this->ideas);
	if (COMMENTS_CANONICAL)
		std::cout <<COLOR_PINK << "Brain" << COLOR_DEFAULT << " copy constructor called"<< std::endl;
}

Brain::~Brain()
{
	if (COMMENTS_CANONICAL)
		std::cout <<COLOR_PINK << "Brain" << COLOR_DEFAULT << " destructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& rhs)
{
	std::copy(rhs.ideas, rhs.ideas + brainSize, this->ideas);
	if (COMMENTS_CANONICAL)
		std::cout <<COLOR_PINK << "Brain" << COLOR_DEFAULT << " copy assignment operator called" << std::endl;
	return *this;
}

const std::string& Brain::getIdea(const unsigned int& pos) const
{
	return (this->ideas[pos]);
}

void Brain::setIdea(const int& pos, const std::string& idea)
{
	ideas[pos] = idea;
}
