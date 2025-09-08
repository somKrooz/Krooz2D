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

void Platformer::TopDownCollisionModel(Vec2& PlayerPosition,BoundingBox PlayerBound , std::vector<CollisionDim>& cols)
{
    // TODO: Make a Collsion For All side For Topdown Games
}

bool Platformer::GetOnGround()
{
    return IsOnGround;
}
