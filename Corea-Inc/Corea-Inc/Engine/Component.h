#pragma once

namespace coconut
{
    class Component
	{
    public:
        virtual ~Component() {};
        virtual void Update(double) {};
    };
}