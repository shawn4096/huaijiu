// huo.c 何师我.霍都
// by snowman 12.feb.98
// Modify by Looklove 2000/10/07

#include <ansi.h>
inherit NPC;
string ask_me();
void check_skills(object ob);
int waiting(object me, object dest);
int checking(object me, object dest);
int do_back(object me);
int do_kill(object me, object dest);
int do_weapon(object me);
void change_huo();

void create()
{
	object me = this_object(); 
     	remove_call_out("create");
     	if (clonep()) tell_room(environment(me),
      	HIY +"霍都转过墙角忽然不见了，接着走出来一个奇丑无比的乞丐。\n\n" NOR, ({me}));
     	me->set_name("何师我", ({"he shiwo", "he", "shiwo"}));     
     	me->set("gender", "男性");
     	me->set("title", "丐帮第十九代弟子");      
     	me->set("age", 35);
     	me->set("unique", 1);
     	me->set("per", 13);
     	me->delete("huodu");
     	me->set("location", 1);
     	me->set("long", "只见他身披一件宽大破烂的黑衣，手持一根酒杯口粗细的铁杖，满头
		乱发，一张脸焦黄臃肿凹凹凸凸的满是疤痕，背上负着五只布袋，原
		来是一名五袋弟子。\n"); 
     
     	me->set("attitude", "friendly");
     	me->create_family("丐帮", 19, "弟子");
     	me->set("str", 23);
     	me->set("int", 24);
     	me->set("con", 22);
     	me->set("dex", 27);  
     	me->set("per", 12);  
     	me->set("chat_chance", 35);
     	me->set("chat_msg", ({ (: random_move :), }));
        me->set("max_qi", 700);
        me->set("max_jing", 700);
        me->set("jingli", 500);
       if (clonep()) me->reincarnate();         
        me->set("combat_exp", 150000);
        me->set_skill("parry", 60);
        me->set_skill("force", 60);
        me->set_skill("dodge", 60);
        me->set_skill("staff", 60);
        me->set_skill("huntian-qigong", 60);       
        me->set_skill("tianshan-zhang", 60);      
        me->set_skill("xiaoyaoyou", 50);
        me->set_skill("suohou-shou", 50);
        me->set_skill("hand", 50);
        me->map_skill("force", "huntian-qigong");
        me->map_skill("dodge", "xiaoyaoyou");
        me->map_skill("hand", "suohou-shou");
        me->map_skill("staff", "tianshan-zhang");
        me->prepare_skill("hand", "suohou-shou");        
        me->set("inquiry", ([ 
            "霍都"  : (: ask_me :), 
            "丐帮" : "我们丐帮是天下第一大帮！\n",                    
            "金轮法王" : "你在说什么啊？",
            "马光佐" : "你在说什么啊？",
            "尹克西" : "你在说什么啊？",
            "尼摩星" : "你在说什么啊？",            
       ]) ); 
        if (clonep()) do_weapon(me);
        setup();               
        remove_call_out("change_huo");          
        if(clonep())
           call_out("change_huo", 900, me);
}       

int do_weapon(object me)
{
   object armor, weapon, *ob;
   int i;
   if(!me) return 0;
   ob = all_inventory(me);
  
   for(i=0; i<sizeof(ob); i++) destruct(ob[i]); 
   if (query("huodu")) armor = new(ARMOR_D("pao2"));
   else armor = new(ARMOR_D("cloth"));
   armor->move(me);
   armor->wear();
   if (query("huodu")) weapon = new(__DIR__"obj/txs");
   else weapon = new(BINGQI_D("gangzhang"));
   weapon->move(me);
   weapon->wield();
   me->add_money("silver", 50);
   return 1;
}

void init()
{
        object ob, me;
        me = this_object();
        ::init();
        if (interactive(ob = this_player()) && visible(ob)){
           if(query("huodu") && ob->query("combat_exp") > 100000) check_skills(ob);
           if(present("yuzhu bang", ob)){      
               message_vision(BLU"$N突然拦在$n面前，眼睛直盯着$n手里的玉竹棒！\n"NOR,me,ob); 
               change_huo();
               ob->start_busy(2); 
               do_kill(me, ob);                                              
               }
           }
}

string get_user_place()
{
        object *obs = users(), ob, room;

        ob = obs[random(sizeof(obs))];  
        room = environment(ob);
        
        if (wiz_level(ob)
        || ob->is_ghost()
        || !room
        || strsrch(file_name(room),"/d/") < 0 
        || !strsrch(base_name(room), "/d/wizard/")
        || !strsrch(base_name(room), "/d/death/")
        || !strsrch(base_name(room), "/d/wuguan/")) 
                return get_user_place();

        else return file_name(room);
                
}
int do_back(object me)
{    
        string room;
        
        remove_call_out("do_back");
        if (!stringp(room = get_user_place()))          
                me->move("/d/city/kedian");
        else me->move(room);  
                             
        tell_room(environment(me), me->query("name")+"快步走了过来。\n", ({me}));       
        me->set_leader(0);
        return 1;
}

string ask_me()
{
        object ob,me;
        ob=this_player();
        me=this_object();
        if(ob->query("combat_exp") < 100000)
           return "小孩子，你自己的名字知道怎么写吗？别问东问西的。\n";
        else{
            if (query("huodu")){
                remove_call_out("check_skills");
                check_skills(ob);
                return "嘿嘿，霍都就是本王子，来耍两套猴戏给我看看吧！\n";
                }
            else{ 
             switch(random(4)) {
               case 0 : return "不知道。\n"; break;
               case 1 : return "我可不认识这个人。\n"; break;       
               case 2 : return "谁是霍都啊？\n"; break;       
               case 3 : change_huo(); 
                        do_kill(me, ob); 
                        return "嘿嘿，霍都就是本王子，来耍两套猴戏给我看看吧！\n";       
                        break;       
                        }                      
            }
         }
}

void change_huo()
{
        int i;
        object *ob, me;
        remove_call_out("change_huo");
        me = this_object();  
  
     tell_room(environment(me), HIY +"突然何师我阴阴一笑，伸手撤去身上的肮脏布衣，又在脸上一抹，竟然
		转眼就变成了一位身着锦袍、风度翩翩的中年公子。\n\n" NOR, ({me}));        
        me->set("title", "蒙古王子");   
        me->set("long", "只见他身穿白边青色长袍，手拿摺扇，
		作贵公子打扮，脸上一股傲狠之色。\n");           
        me->set_name("霍都", ({"huo du", "huo", "du"}));
        me->set("shen", -12000);
        me->set("per", 25);
        me->set("huodu", 1);
        me->set_skill("parry", 100);
        me->set_skill("force", 100);
        me->set_skill("dodge", 100);
        me->set_skill("sword", 100);
        me->set_skill("songshan-qigong", 120);       
        me->set_skill("songshan-jian", 120);      
        me->set_skill("xiaoyaoyou", 120);
        me->set_skill("suohou-shou", 120);
        me->set_skill("hand", 100);
        me->map_skill("force", "songshan-qigong");
        me->map_skill("dodge", "xiaoyaoyou");
        me->map_skill("hand", "suohou-shou");
        me->map_skill("sword", "songshan-jian");
        me->prepare_skill("hand", "suohou-shou");
        me->set("combat_exp", 300000);
        me->set("max_qi", 1500);
        me->set("max_jing", 1300);
        me->set("eff_jingli", 1400);
        me->set("jiali", 50);
        me->reincarnate();   
        me->set("chat_chance_combat", 20);
        me->set("chat_msg_combat", ({ (: perform_action, "sword.feiwu" :) }));  
        if (!environment()->query("no_fight")) {
        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
                if(!userp(ob[i])) continue;
                if(me->query_temp("block_msg/all")) continue;
                if(!living(me))continue;
             	if(ob[i]->query("combat_exp") < 100000) continue;
                COMBAT_D->do_attack(me, ob[i], me->query_temp("weapon"),1);
        }
        }
        do_weapon(me);
        remove_call_out("create");
        if (clonep())
            call_out("create", 300+random(200), me);           
}

void kill_ob(object ob)
{       
      if (query("huodu")) return;  
      else change_huo(); 
}

void reset()
{
  if (clonep()) do_back(this_object());
}
#include "killer.h";
