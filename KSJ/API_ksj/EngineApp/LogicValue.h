#pragma once

//용도 :
//설명 :
class Player;
class Monster;
class PlayScene;
class LogicValue
{
public:
    //몬스터와 맵오브젝트 플레이어는 y값에따라 정렬합니다.
    enum class RenderGroup
    {
        BackGround = 0,
        Shadow = 1,
        UI = 2,
        Pit =5,
        Tear = 10000,
        BossAniUI1 = 17000,
        BossAniUI2 = 17001,
        Item = 10003,
        ItemEffect = 17004,
        ItemUIEffect = 17005,
        DieUI = 17006,
    };

    enum class CollisionGroup
    {
        Player,
        PlayerHead,
        PlayerTear,
        Enemy,
        EnemyTear,
        MapObject,
        MapEnemyObject,
        ShopItemObject,
        Bomb,
        BombObject,
        PlayerItem,//아이템 (폭탄 키 동전 아님) 코스튬아이템
        Spikes,
        Pit,
        Protection,
        research,//플레이어찾기용
    };

    enum class RoomType {
        Space,
        Room,
        Treasure,
        Secret,
        Boss,
        FinalBoss,
        Shop,
        Max
    };

    enum class RoomImageGroup
    {
        Basement1,
        Basement2,
        Basement3,
        Basement4,
        Basement5,
        Max,

    };
    //Room은 적이있는 방
    //NotEnemyRoom은 적이없는방
    enum class RoomInfoGroup {
        Room1,
        Room2,
        Room3,
        Room4,
        Room5,
        Room6,
        Room7,
        Room8,
        Room9,
        Room10,
        Room11,
        Room12,
        Room13,
        NotEnemyRoom1,
        NotEnemyRoom2,
        Max
    };
    enum class ItemType {
        Coin,
        Bomb,
        Heart,
        Max
    };
    enum class ItemBoxType
    {
        Treasure_box,
        BombAttack_box,
        Max
    };
    enum class BossType {
        flyBoss,
        mom,
        question,
        Max
    };

    enum class EnemyType {
        Fly,
        Pooter,
        full_fly,
        Nerveending,
        Psychic_horf,
        Onetooth,
        Horf,
        Host,
        Redmaw,
        Sucker,

        MAX,
    };
    enum class EditorActorType {
        Fly,
        Pooter,
        Boomfly,
        full_fly,
        Deathshead,
        Nerveending,
        Psychicmaw,
        Psychic_horf,
        Onetooth,
        Redboomfly,
        Bomb,
        BonFire,
        Poop,
        Stone,
        Horf,
        Dinga,
        Dip,
        Host,
        Moms_hand,
        Redmaw,
        Squirt,
        Sucker,
        Turret,

        //Grid
        Spikes,
        PitLeftTop,
        PitTop,
        PitRightTop,
        PitLeft,
        PitCenter,
        PitRight,
        PitLeftBottom,
        PitBottom,
        PitRightBottom,
        BoxItem,
        MAX,
    };
    enum class ItemGroup {
        haloofflies,
        lunch,
        momslipstick,
        thesadonion,
        Wirecoathanger,
        HolyGrail,
        Familiar_brotherbobby,
        Familiar_littlechad,
        Familiar_sackofpennies,
        Familiar_sistermaggie,
        Active_Necronomicon,
        Active_Kamikaze,
        Mutantspider,
        Polyphemus,
        Spoonbender,
        Catoninetails,
        MAX,
    };
    static Player* MainPlayer;


    static PlayScene* MainScene;
};

enum class Dir {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    MAX,
};
