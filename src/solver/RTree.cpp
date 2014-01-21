#include <memory>

#include <spatialindex/SpatialIndex.h>
#include <spatialindex/RTree.h>
#include <spatialindex/tools/Tools.h>

#include "defs.hpp"
#include "BoxQuery.hpp"
#include "RTree.hpp"
#include "State.hpp"
#include "StateInfo.hpp"
#include "VectorState.hpp"

namespace solver {
RTree::RTree(unsigned long nSDim, StatePool *statePool) :
        nSDim_(nSDim),
        statePool_(statePool),
        properties_(nullptr),
        storageManager_(nullptr),
        tree_(nullptr) {
    reset();
}

void RTree::reset() {
    properties_ = std::make_unique<Tools::PropertySet>();
    Tools::Variant var;

    var.m_varType = Tools::VT_ULONG;
    var.m_val.ulVal = nSDim_;
    properties_->setProperty("Dimension", var);

    var.m_varType = Tools::VT_ULONG;
    var.m_val.ulVal = 100;
    properties_->setProperty("IndexCapacity", var);

    var.m_varType = Tools::VT_ULONG;
    var.m_val.ulVal = 100;
    properties_->setProperty("LeafCapacity", var);

    var.m_varType = Tools::VT_DOUBLE;
    var.m_val.dblVal = 0.7;
    properties_->setProperty("FillFactor", var);

    var.m_varType = Tools::VT_LONG;
    var.m_val.lVal = SpatialIndex::RTree::RV_RSTAR;
    properties_->setProperty("TreeVariant", var);

    tree_.reset(nullptr);
    storageManager_.reset(
            SpatialIndex::StorageManager::returnMemoryStorageManager(*properties_));
    tree_.reset(SpatialIndex::RTree::returnRTree(*storageManager_, *properties_));
}

void RTree::addStateInfo(StateInfo *stateInfo) {
    SpatialIndex::id_type stateId = stateInfo->getId();
    std::vector<double> vectorData = static_cast<VectorState*>(stateInfo->getState())->asVector();
    SpatialIndex::Point point(&vectorData[0], nSDim_);
    tree_->insertData(0, nullptr, point, stateId);
}

void RTree::removeStateInfo(StateInfo *stateInfo) {
    SpatialIndex::id_type stateId = stateInfo->getId();
    std::vector<double> vectorData = static_cast<VectorState*>(stateInfo->getState())->asVector();
    SpatialIndex::Point point(&vectorData[0], nSDim_);
    tree_->deleteData(point, stateId);
}

StateInfo *RTree::getNearestNeighbor(StateInfo */*stateInfo*/) {
    return nullptr;
}

std::unique_ptr<BoxQuery> RTree::makeBoxQuery() {
    return std::make_unique<BoxQuery>(nSDim_, statePool_, tree_.get());
}

} /* namespace solver */
