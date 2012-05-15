## Copyright (C) 2012 az
## 
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## init

## Author: az <az@az-think>
## Created: 2012-05-14

function [ ret ] = init ()
	
	x = linspace(0, 100);	
	Crno = @(x) max((-0.75/50).*x+1, 0);
	Belo = @(x) max((0.75/50).*x-0.5, 0);


	Levo = @(x) (-0.5/50).*x+1;
	Desno = @(x) (0.5/50).*x;
	
	#clf
	#hold on
	#grid on
	#plot(x, Belo(x), 'r')
	#plot(x, Crno(x), 'k')
	
	#figure
	#clf
	#hold on
	#plot(x, Levo(x), 'r')
	#plot(x, Desno(x), 'g')

	input = 95;

	k = 100;

	rng = 0:(100/k):100;
	b = Belo(rng);
	c = Crno(rng);

	l = Levo(rng);
	d = Desno(rng);

	#B = repmat(Belo(input), k, k);
	#D = repmat(d, 6, 1);

	R1 = Belo(input)
	
	#C = repmat(Crno(input), k, k);
	#L = repmat(l, 6, 1);
	
	R2 = Crno(input)


	Y1 = bsxfun(@min, repmat(R1, 1, k+1), d);
	Y2 = bsxfun(@min, repmat(R2, 1, k+1), l);


	Y = max([Y1;Y2])

	cog = sum(Y.*rng)/sum(Y)

	clf
	hold on
	plot(rng, Y);
	plot(rng, d, 'r')
	plot(rng, l, 'k')	

	#AA = repmat(A', 1, 6)
	#R	
	#RR = bsxfun(@min, AA, R)

	#ret = max(RR);

	#plot(rng, ret, 'LineWidth', 3);


	
endfunction
