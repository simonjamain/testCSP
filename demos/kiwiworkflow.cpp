#include <kiwi/kiwi.h>
#include <stdio.h>

int main( int argc, const char* argv[] )
{
    //Instancier un kiwi::solver
    kiwi::Solver solver;

    //Créer une kiwi::variable pour chaque variable du système
    kiwi::Variable min("min");
    kiwi::Variable max("max");
    kiwi::Variable prevDate("prevDate");
    kiwi::Variable nextDate("nextDate");

    // - On assigne à ces variable une valeure initiale
    min.setValue(5);
    max.setValue(15);
    prevDate.setValue(0);
    nextDate.setValue(10);

    //Créer et ajouter des kiwi::constraint portant sur ces variables avec pour chacune une kiwi::strength associée
    // - Ici les premières contraintes que l'on pose correspondent à notre "modèle",
    //   ce sont des contraintes requises qui définisse la consistance du système
    kiwi::Constraint cstrMinSuppZero(min >= 0, kiwi::strength::required);
    solver.addConstraint(cstrMinSuppZero);

    kiwi::Constraint cstrNextDateMin(nextDate >= min + prevDate, kiwi::strength::required);
    solver.addConstraint(cstrNextDateMin);

    kiwi::Constraint cstrNextDateMax(nextDate <= max + prevDate, kiwi::strength::required);
    solver.addConstraint(cstrNextDateMax);

    // - On appelle "stay" les contraintes qui indiquent aux variables de "ne pas bouger",
    //   on les initialise en général au début du mouvement et on règle leur poid en fonction du comportement voulu.
    //   ici par exemple, on préfère que les dates bougent plutôt que les durées des contraintes (sauf default qui n'est pas représenté ici)
    kiwi::Constraint stayMin(min == min.value(), kiwi::strength::strong);
    solver.addConstraint(stayMin);

    kiwi::Constraint stayMax(max == max.value(), kiwi::strength::strong);
    solver.addConstraint(stayMax);

    kiwi::Constraint stayPrevDate(prevDate == prevDate.value(), kiwi::strength::weak);
    solver.addConstraint(stayPrevDate);

    kiwi::Constraint stayNextDate(nextDate == nextDate.value(), kiwi::strength::weak);
    solver.addConstraint(stayNextDate);

    //Annoncer les variables dont on veux proposer des nouvelles valeures grace à kiwi::solver::addEditVariable() en leur associant une kiwi::strength différente de required
    // - ici, on veut déplacer le timenode next
    // Note: on ne peut pas ici mettre de force required à une édit variable car si l'utilisateur faisait un déplacement impossible, cela ferait crasher le système
    solver.addEditVariable(nextDate, kiwi::strength::medium);

    //Proposer des nouvelles valeures pour les "variables d'édition" avec kiwi::solver::suggestValue()
    solver.suggestValue(nextDate, 20);

    //Résoudre le système** grâce à kiwi::solver::updateVariables()
    solver.updateVariables();
    // - affichons le resultat
    std::cout << "prevDate(" << prevDate.value() << ") -------- prevDate+min(" << prevDate.value() + min.value() << ") ------- nextDate(" << nextDate.value() << ") -------- prevDate+max(" << prevDate.value() + max.value() << ")\n";

    //"Relacher" les "variables d'édition" avec kiwi::solver::removeEditVariable()
    solver.removeEditVariable(nextDate);

    return 0;
}
