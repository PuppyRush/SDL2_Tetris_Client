//
// Created by chaed on 18. 11. 25.
//

#ifndef TERIS_FIGURE_CLASS_TFIGURELBUILDER_H
#define TERIS_FIGURE_CLASS_TFIGURELBUILDER_H

#include "TFigureBuilder.h"

namespace tetris {

class TFigureLBuilder : public TFigureBuilder {
public:

    TFigureLBuilder(const TPoint &point);

    virtual ~TFigureLBuilder();

    virtual TFigureLBuilder *color(const TColor &color) override;
    virtual TFigureLBuilder *type(const TFigureType &type) override;
    virtual TFigureLBuilder *age(const t_age &age) override;
    virtual std::shared_ptr <TFigure> build() const override;
    
    
    
private:

    
};

}
#endif //TERIS_FIGURE_CLASS_TFIGURELBUILDER_H
