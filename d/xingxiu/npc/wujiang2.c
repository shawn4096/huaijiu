// wujiang.c 武将
inherit NPC;
string ask_me();
void create()
{
        set_name("侯君集", ({ "hou junji", "hou", "junji" }));
        set("gender", "男性");
        set("age", 45);
        set("str", 35);
        set("int", 19);
        set("con", 30);
        set("dex", 20);
        set("long", "侯君集是这里的守将，他曾跟李靖学习兵法，善能用兵。\n");
        set("combat_exp", 350000);
        set("attitude", "peaceful");
       set("max_qi", 1200);
       set("max_jing", 1200);
       set("eff_jingli", 1000);
       set("jiali", 30);
       set_skill("force", 70); 
       set_skill("unarmed", 80);
       set_skill("strike", 70);
       set_skill("sword", 70);
       set_skill("dodge", 70);
       set_skill("parry", 70);
       set_skill("qingmang-jian", 80); 
       map_skill("sword", "qingmang-jian");
       map_skill("parry", "qingmang-jian");
       map_skill("parry", "qingmang-jian");
       set("inquiry", ([              
		"通缉" : (: ask_me :),
		"帮忙" : (: ask_me :),
       ]));
        setup();
        carry_object(BINGQI_D("gangjian"))->wield();
        carry_object(ARMOR_D("armor"))->wear();
}

void kill_ob(object me)
{     
   int i;
   object ob;
   if(!this_object()->is_killing(me->query("id"))){  
    command("say 大胆！");
    command("say 来人！将"+me->name()+"给我抓起来！\n");
    me->apply_condition("killer", me->query_condition("killer")+150); 
    message_vision("四周的武将开始对$N发动攻击！\n", me);
    for(i=0; i<2; i++) {
     if(objectp(ob = present("wu jiang "+(i+1), environment(this_object()))))
         ob->kill_ob(me);    
     }  
    }
   ::kill_ob(me);
}

int accept_object(object me, object obj)
{            
	int i = me->query("combat_exp")/20000 + me->query_condition("killer") / 2 + me->query("PKS") * 10;

	i *= 10000;
	if (i < 200000) i = 200000;
      if(obj->query("money_id")){
        if(me->query_condition("killer") && me->query_temp("hou_ask")){
          if(obj->value() >= i){
              command("haha " + me->query("id"));
              command("whisper "+me->query("id")+" 你就放心吧，这件事包在我身上！");
              me->clear_condition("killer");
              me->delete_temp("hou_ask");
          log_file("quest/tongji",sprintf("%s %s(%s)花费 %d 买通缉。\n",
            ctime(time())[4..19],me->name(1), capitalize(getuid(me)), i));
              return 1;
              }
          else {
              command("say 才这么点钱能干什么？");
              return 1;
              }
          }
        else {
             command("say 嘿嘿，那就多谢了！");
             return 1;
             }
      }
      command("hmm " + me->query("id"));
      command("say 我对"+obj->name()+"不稀罕。");
      return 0;
}

string ask_me()
{
	object me = this_player();
	int i = me->query("combat_exp")/20000 + me->query_condition("killer") / 2 + me->query("PKS") * 10;
    
    if(!me->query_condition("killer")) return "帮你什么忙？别烦我！";
	if (i < 20) i = 20;
    me->set_temp("hou_ask", 1);
    message_vision("\n$N对着$n嘿嘿一笑：杀了人被通缉了是吧？\n", this_object(), me);
    command("whisper "+me->query("id")+" "+chinese_number(i)+"两黄金。");
    return "办法是有，不过……嘿嘿，你应该知道该怎么做吧？\n";    
}
