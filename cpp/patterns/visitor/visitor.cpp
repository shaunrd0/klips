
#include "visitor.hpp"


/******************************************************************************/
// Concrete components

void Gear::accept(PartVisitor *v)
{
  v->visit(this);
}

void Spring::accept(PartVisitor *v)
{
  v->visit(this);
}


/******************************************************************************/
// Concrete visitors

void PartVisitor::visit(Gear *g)
{
  std::cout << g->getName() << " is price " << g->getPrice() << " with radius of "
            << g->getRadius() << std::endl;
}

void PartVisitor::visit(Spring *g)
{
  std::cout << g->getName() << " is price " << g->getPrice()
            << " with elasticity of " << g->getElasticity() << std::endl;
}
