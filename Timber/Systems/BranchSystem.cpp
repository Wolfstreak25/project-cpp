#include "BranchSystem.hpp"
#include "Config/Constants.hpp"

namespace Timber {
	void BranchSystem::Init(const sf::Texture& texture, int count) {
		m_branches.clear();
		for (int i = 0; i < count; i++) {
			m_branches.emplace_back(std::make_unique<Branch>(texture, i));
		}
	}

	void BranchSystem::ShiftBranches() {
		std::vector<Side>oldSides;
		for (auto& branch : m_branches) {
			oldSides.push_back(branch->GetSide());
		}

		for (int i = static_cast<int>(m_branches.size()) - 1; i > 0; --i) {
			m_branches[i]->SetSide(oldSides[i - 1]);
		}

		m_branches[0]->SetRandomSide();
	}

	void BranchSystem::ResetAll() {
		for (auto& branch : m_branches) {
			branch->ResetBranch();
		}
	}

	Side BranchSystem::GetBottomBranchSide() const {
		if (m_branches.empty()) {
			return Side::None;
		}
		return m_branches.back()->GetSide();
	}

	void BranchSystem::Draw(sf::RenderWindow& window) const {
		for (auto& branch : m_branches) {
			branch->Draw(window);
		}
	}

	const std::vector<std::unique_ptr<Branch>>& BranchSystem::GetBranches()const {
		return m_branches;
	}
}