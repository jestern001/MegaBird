    #include <genesis.h>
    #include <resources.h>


    // edges of the field
    const int LEFT_EDGE = 0;
    const int RIGHT_EDGE = 320;
    const int TOP_EDGE = 0;
    const int BOTTOM_EDGE = 224;

    // init ball
    Sprite* ball;
    int ball_pos_x = 100;
    int ball_pos_y = 100;
    int ball_vel_x = 1;
    int ball_vel_y = 1;
    int ball_width = 8;
    int ball_height= 8;

    // init paddle
    Sprite* player;
    int player_pos_x = 144;
    const int player_pos_y = 200;
    int player_vel_x = 0;
    const int player_width = 32;
    const int player_height = 8;

    // score varibles
    int score = 0;
    char lable_score[6] = "SCORE\0";
    char str_score[4] = '0';

    void myJoyHandler(u16 joy, u16 changed, u16 state) {
        if (joy == JOY_1) {
            if (state & BUTTON_RIGHT) {
                player_vel_x = 3;
            } else if (state & BUTTON_LEFT) {
                player_vel_x = -3;
            } else {
                if ( (changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT) ) {
                    player_vel_x = 0;
                }
            }
        }
    }

    void movePlyaer(){
        player_pos_x += player_vel_x;
        if (player_pos_x < LEFT_EDGE) player_pos_x = LEFT_EDGE;
        if (player_pos_x + player_width > RIGHT_EDGE) player_pos_x = RIGHT_EDGE - player_width;
        SPR_setPosition(player, player_pos_x, player_pos_y);
    }

    void moveBall(){
        // horizontal bounds
        if(ball_pos_x < LEFT_EDGE){
            ball_pos_x = LEFT_EDGE;
            ball_vel_x = -ball_vel_x;
        } else if(ball_pos_x + ball_width > RIGHT_EDGE){
            ball_pos_x = RIGHT_EDGE - ball_width;
            ball_vel_x = -ball_vel_x;
        }

        // verticle bounds
        if(ball_pos_y < TOP_EDGE){
            ball_pos_y = TOP_EDGE;
            ball_vel_y = -ball_vel_y;
        } else if(ball_pos_y + ball_height > BOTTOM_EDGE){
            ball_pos_y = BOTTOM_EDGE - ball_height;
            ball_vel_y = -ball_vel_y;
        }

        if(ball_pos_x < player_pos_x + player_width && ball_pos_x + ball_width > player_pos_x){
            if(ball_pos_y < player_pos_y + player_height && ball_pos_y + ball_height >= player_pos_y){
                //On collision, invert the velocity
                ball_pos_y = player_pos_y - ball_height - 1;
                ball_vel_y = -ball_vel_y;
            }
        }

        // update position based on velocity
        ball_pos_x += ball_vel_x;
        ball_pos_y += ball_vel_y;

        SPR_setPosition(ball, ball_pos_x, ball_pos_y);
    }

    int main()
    {
        // set up input handler
        JOY_init();
        JOY_setEventHandler( &myJoyHandler );

        // Load our tileset
        VDP_loadTileSet(bgtile.tileset,1,DMA);
        PAL_setPalette(PAL1, bgtile.palette->data, DMA);
        VDP_fillTileMapRect(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,0,40,30);

        SPR_init();
        ball = SPR_addSprite(&imgball, 100, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        player = SPR_addSprite(&paddle, player_pos_x, player_pos_y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        
        while(1)
        {
            //Do cool stuff in a loop!
            moveBall();
            movePlyaer();
            SPR_update();
            SYS_doVBlankProcess();
        }

        //Stop doing cool stuff :(
        return(0);
    }
