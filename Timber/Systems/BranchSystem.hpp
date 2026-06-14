#pragma once 
#include "Entities/Branch.hpp"
#include <memory>
#include <vector>

namespace Timber {
	class BranchSystem
	{
	public:
		BranchSystem() = default;

		/// Initialize the branches with the given texture.
		void Init(const sf::Texture& texture, int count);

		/// Shift all branches down and generate a new top branch.
		void ShiftBranches();

		/// Reset all branches to Side::None
		void ResetAll();

		/// Get the side of the bottom branch (for collision check).
		Side GetBottomBranchSide() const;

		/// Draw all branches.
		void Draw(sf::RenderWindow& window) const;

		/// Acess individual branches
		const std::vector<std::unique_ptr<Branch>>& GetBranches() const;
	private:
		std::vector<std::unique_ptr<Branch>> m_branches;
	};
}