# Game structure  
## Game cycle illustration  
Sketch of our game workflow  
```mermaid
flowchart LR
A([ Welcoming\n message]) --- B0{Choose or create\nplayer?}
B0 -.- B([get_menu_choice])
B -.->| choose | D([get_all_players]) -.- C([get_menu_choice])
D -.-| no players yet |E
B -.->| create | E([get_player_name]) -.- F([create\nPlayer])

C -.- R{Main menu}
F -.- R

R -->| change player | R1{Load\nor\ncreate?}
R1 -.->| load | G1([get_all_players]) -.- G2([get_menu_choice]) -.-> R
G1-.-| no players yet |G3
R1 -.->| create | G3([get_player_name]) -.- G4([create\nPlayer]) -.-> R

R -->| change difficulty | R2{What's new\nlevel?}
R2 -.- H1([get_menu_choice]) -.- H2([set_level]) -.-> R

R -->| delete player | J1([delete\nPlayer]) --- R1
R -->| start training | I([generate_text]) -.- R3([play]) -.- I1([add new statistics]) -.-| if player not found | I2([store new player]) -.-> R
R -->| get help | R4([help_message]) -.-> R
R -->| exit | Ex([Goodbye\nmessage]) -.- Exi( Exit )

style A fill:#bbf
style R fill:#bbf
style R3 fill:#bbf
style Exi fill:#bbf
style J1 fill:#bbb
```
## Code structure  
```mermaid
graph TD
A([cli.cpp]) --- A1[Command line\nspecific instructions\nViewer]
B([engine.cpp])
C([database.cpp])
D([player.cpp])
E[statistics.csv] --- E1[ - Name\n - Max speed\n - Presicion\n - Games number]
T([tt.cpp])

B --> | loading\storing |C 
B --> | player maintenance |D
B --> | viewer functions |A 
T -.-> |game cycle| B
C -.- E
D --- D1[" - _name \n - _level\n - _speed\n - _performance\n - _total_games\n + Player(name)\n + Player(name,level)\n + get_name()\n + get_level()\n + set_level\n + get_stats()\n + post_game_update()"]
```
## Further functionality  
Further functionality might be:  
 - adding delete-user functionality :tired_face:  
 - building web-interface wrapping
 - moving database from plain-text storage to real databases (like SQL)
 - in-building more STL for optimality  
 - anything you might think of: from live clock to key-specific statistics :ok_hand:
