/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:05:16 by mamuller          #+#    #+#             */
/*   Updated: 2022/04/22 16:05:16 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

#define COMMENTS_CANONICAL 0

#define COLOR_PINK "\033[38;5;200m"
#define COLOR_DEFAULT "\033[0m"

class Brain
{
public:
	Brain();
	Brain(const Brain& obj);
	~Brain();
	Brain& operator=(const Brain& rhs);

	const std::string& getIdea(const unsigned int& pos) const;
	void setIdea(const int& pos, const std::string& idea);

	static const unsigned int brainSize = 100;
private:
	std::string ideas[brainSize];
};