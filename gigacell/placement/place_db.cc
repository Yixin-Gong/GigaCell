//
// Created by eric on 23-9-15.
//

#include "place_db.h"

namespace gigaplace {
    void PlaceDB::init() {
        Net2Mos net2mos{};
        std::vector<Net2Mos> net{};
        index idx = 0;
        for (auto &nmos: db_.nmos_list()) {
            net2mos.idx = idx;
            net2mos.type = 0;
            if (nets_.find(nmos.getDrain()) == nets_.end()) {
                nets_.emplace(nmos.getDrain(), net);
                net2mos.electrode_name = "drain";
                nets_.find(nmos.getDrain())->second.emplace_back(net2mos);
            } else if (nets_.find(nmos.getDrain()) != nets_.end()) {
                net2mos.electrode_name = "drain";
                nets_.find(nmos.getDrain())->second.emplace_back(net2mos);
            }
            if (nets_.find(nmos.getGate()) == nets_.end()) {
                nets_.emplace(nmos.getGate(), net);
                net2mos.electrode_name = "gate";
                nets_.find(nmos.getGate())->second.emplace_back(net2mos);
            } else if (nets_.find(nmos.getGate()) != nets_.end()) {
                net2mos.electrode_name = "gate";
                nets_.find(nmos.getGate())->second.emplace_back(net2mos);
            }
            if (nets_.find(nmos.getSource()) == nets_.end()) {
                nets_.emplace(nmos.getSource(), net);
                net2mos.electrode_name = "source";
                nets_.find(nmos.getSource())->second.emplace_back(net2mos);
            } else if (nets_.find(nmos.getSource()) != nets_.end()) {
                net2mos.electrode_name = "source";
                nets_.find(nmos.getSource())->second.emplace_back(net2mos);
            }
            idx++;
        }
        idx = 0;
        for (auto &pmos: db_.pmos_list()) {
            net2mos.idx = idx;
            net2mos.type = 1;
            if (nets_.find(pmos.getDrain()) == nets_.end()) {
                nets_.emplace(pmos.getDrain(), net);
                net2mos.electrode_name = "drain";
                nets_.find(pmos.getDrain())->second.emplace_back(net2mos);
            } else if (nets_.find(pmos.getDrain()) != nets_.end()) {
                net2mos.electrode_name = "drain";
                nets_.find(pmos.getDrain())->second.emplace_back(net2mos);
            }
            if (nets_.find(pmos.getGate()) == nets_.end()) {
                nets_.emplace(pmos.getGate(), net);
                net2mos.electrode_name = "gate";
                nets_.find(pmos.getGate())->second.emplace_back(net2mos);
            } else if (nets_.find(pmos.getGate()) != nets_.end()) {
                net2mos.electrode_name = "gate";
                nets_.find(pmos.getGate())->second.emplace_back(net2mos);
            }
            if (nets_.find(pmos.getSource()) == nets_.end()) {
                nets_.emplace(pmos.getSource(), net);
                net2mos.electrode_name = "source";
                nets_.find(pmos.getSource())->second.emplace_back(net2mos);
            } else if (nets_.find(pmos.getSource()) != nets_.end()) {
                net2mos.electrode_name = "source";
                nets_.find(pmos.getSource())->second.emplace_back(net2mos);
            }
            idx++;
        }
    }
}


