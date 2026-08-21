# C++ Formatting Standard
I kinda care about your style, but not too much. I just want it to be readable.
## naming
Naming stuff is pretty straightforward. I do not care about your naming style, whether it be:

camelCase

PascalCase

snake_case

or even kebab-case

However, I do not want to see the following be names of a function, variable, or class/struct:

	int n

	class cs: public s

A normal programmer would not understand what in the world those would mean, but these:

	int capybaras;

	class Capybara: public Animal

	{

		//no

	}

	void Capy()
	{
		//STUFF HERE
	}

are pretty much what I want

## indentation
so basically, its either 4 spaces or 1 tab, I don't care which.

this is fine:
    
	{
	    four spaces of pure space
	}
	
and also this:

	{
		these are indented with a tab
	}

you see what I'm talking about, right?

but please do not use both, only use 1 style for indentation. because then it looks wrong on a markdown file.

## braces
so basically I want something like

	if (condition)
	{
		//do stuff
	}
	else
	{
		//do other stuff
	}

do you see how the braces are on their own line? I want that. I don't want this:

	if (condition) {
		//do stuff
	} else {
		//do other stuff
	}

also, what the hell is this?

	if(condition){//do somethin}

never do that.

okay thats it bye