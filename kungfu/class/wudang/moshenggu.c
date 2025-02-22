// moshenggu.c
// by ydh

inherit NPC;

int ask_me_1(object who);
int ask_raozhi();

void create()
{
        set_name("莫声谷", ({ "mo shenggu", "mo" }));
        set("nickname", "武当七侠");
        set("long", 
                "他就是张三丰的七弟子莫声谷。\n"
                "他年纪最轻，但身材魁梧，精明能干。\n");
        set("gender", "男性");
        set("age", 22);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 30);
        set("con", 26);
        set("dex", 28);
        
        set("max_qi", 1200);
        set("max_jing", 800);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 100000);
        set("score", 50000);

        set_skill("force", 80);
        set_skill("yinyun-ziqi", 60);
        set_skill("dodge", 80);
        set_skill("tiyunzong", 60);
        set_skill("cuff", 80);
        set_skill("taiji-quan", 60);
        set_skill("parry", 80);
        set_skill("sword", 80);
        set_skill("taiji-jian", 70);
        set_skill("taoism", 80);
        set_skill("literate", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        prepare_skill("cuff", "taiji-quan");
        create_family("武当派", 2, "弟子");
        set("inquiry", ([
                "下山" : (: ask_me_1 :),
                "绕指柔剑" : (: ask_raozhi :),
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}

int ask_raozhi()
{
     object me = this_player();
     mapping myfam;
      myfam = (mapping)me->query("family");
     if (!myfam || myfam["family_name"] != "武当派") {    
          command("kick3 "+(string)me->query("id"));
          command("say 你非我派弟子，随便打听什么？");
          return 1; }
     if (me->query_temp("raozhi")) {
         command("say 不是告诉你了么？");
         return 1; } else {
         command("say 那是恩师传给我的一门特殊剑招。");
         command("say 我新学不久，无法精通，你还是亲自去请教他吧。");
         me->set_temp("raozhi",1);
         return 1; }
}

int ask_me_1(object who)
{ object me;
  mapping myfam;
  me=this_player();
  myfam = (mapping)me->query("family");
 if (!myfam || myfam["family_name"] != "武当派") 
  { command("slap "+(string)me->query("id"));
    command("say 你非我派弟子，也敢来滥竽充数!\n");
    return 1;
  }
 if ( (int)me->query_skill("yinyun-ziqi", 1) < 20)
   {
    command("pat "+(string)me->query("id"));
    command("say 你武艺未成，还是别下山的好!\n");
    return 1;
   }
  if((int)me->query("wudang_given")<(int)me->query("age")) 
  {
    command("nod "+(string)me->query("id"));
    who->add_money("gold",(int)(me->query_skill("yinyun-ziqi", 1)/10) );
    command("give "+me->query("id")+" "+(int)(me->query_skill("yinyun-ziqi", 1))/10+" gold");
    me->set("wudang_given",(int)me->query("age"));
  }
  command("say 你下山后要多行侠仗义，要是为非做歹，我必清理门户!\n");
  return 1;
}

