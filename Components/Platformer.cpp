#include "Platformer.h"

Platformer::Platformer(Vec2& NextPos ,Vec2& Velocity ,BoundingBox PlayerDim , std::vector<CollisionDim> dims)
{
    PlayerBound = PlayerDim;
    IsOnGround = false;

    for(auto cols : dims){
        auto TilePos = cols.Position;
        auto TileSize = cols.Size;
        BoundingBox TileBound{TilePos.x , TilePos.x + TileSize.x ,TilePos.y , TilePos.y + TileSize.y};

        if(PlayerBound.Right > TileBound.Left && PlayerBound.Left < TileBound.Right &&
        PlayerBound.Bottom > TileBound.Top && PlayerBound.Top < TileBound.Bottom )
        {
            float OverlapX1 = PlayerBound.Right - TileBound.Left; 
            float OverlapX2 = TileBound.Right - PlayerBound.Left;
            
            float OverlapY1 = TileBound.Bottom - PlayerBound.Top;
            float OverlapY2 = PlayerBound.Bottom - TileBound.Top;

            // Find Axis
            if(std::min(OverlapX1 , OverlapX2) < std::min(OverlapY1 , OverlapY2))
            {
                // Horizontal Collision
                if(OverlapX1 < OverlapX2) NextPos.x -= OverlapX1;
                else NextPos.x += OverlapX2;
                Velocity.x = 0;

            }else
            {
                // Vertical Collision   
                if(OverlapY1 < OverlapY2)
                {
                    NextPos.y += OverlapY1;
                    if(Velocity.y > 0) Velocity.y = 0;
                }else {
                    NextPos.y -= OverlapY2;
                    IsOnGround = true;
                    if(Velocity.y > 0) Velocity.y = 0;
                }
            }

        }
    }
}

void Platformer::TopDownCollisionModel(Vec2& NextPos, BoundingBox PlayerDim, std::vector<CollisionDim>& dims)
{
    for (auto& cols : dims) {
        BoundingBox TileBound{
            cols.Position.x,
            cols.Position.x + cols.Size.x,
            cols.Position.y,
            cols.Position.y + cols.Size.y
        };

        // Check overlap
        if (PlayerDim.Right > TileBound.Left && PlayerDim.Left < TileBound.Right &&
            PlayerDim.Bottom > TileBound.Top && PlayerDim.Top < TileBound.Bottom)
        {
            // Calculate overlap along each axis
            float OverlapX1 = PlayerDim.Right - TileBound.Left;
            float OverlapX2 = TileBound.Right - PlayerDim.Left;
            float OverlapY1 = TileBound.Bottom - PlayerDim.Top;
            float OverlapY2 = PlayerDim.Bottom - TileBound.Top;

            // Resolve on the smaller overlap axis
            if (std::min(OverlapX1, OverlapX2) < std::min(OverlapY1, OverlapY2)) {
                // Horizontal
                if (OverlapX1 < OverlapX2) NextPos.x -= OverlapX1;
                else NextPos.x += OverlapX2;
            } else {
                // Vertical
                if (OverlapY1 < OverlapY2) NextPos.y += OverlapY1;
                else NextPos.y -= OverlapY2;
            }
        }
    }
}


bool Platformer::GetOnGround()
{
    return IsOnGround;
}
