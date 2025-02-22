// chen.c 陈长老
// Modify by Looklove@SJ 2000/9/27
// Update by Yanqi 10/04/2k
// MOdify By Looklove 2000/10/9

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_fangqi();
string ask_dan();
string ask_whip();
int ask_job();
int ask_trap();
string get_place(string str);
int check(object ob);

void create()
{
        set_name("陈长老", ({"chen zhanglao", "chen", "zhanglao"}));
        set("title", "丐帮九袋长老");
        set("nickname", "长臂叟");
        set("gender", "男性");
        set("unique", 1);
        set("no_quest",1);
        set("no_bark",1);
        set("age", 56);
        set("long","他乃丐帮六大长老之一，使的是一只麻包袋，甚是怪异。\n");
        set("attitude", "peaceful");
        set("dan_count",200);
        
        set("str", 25);
        set("int", 23);
        set("con", 25);
        set("dex", 23);
        set("qi", 2100);
        set("max_qi", 2100);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 50);
        
        set("combat_exp", 700000);
        set("apprentice", 1);
        
        set_skill("force", 120); // 基本内功
        set_skill("huntian-qigong", 120); // 混天气功
        set_skill("unarmed", 120); // 基本拳脚
        set_skill("dodge", 140); // 基本躲闪
        set_skill("xiaoyaoyou", 140); // 千里行乞 
        set_skill("parry", 120); // 基本招架
        set_skill("whip", 140);
        set_skill("begging", 110);
        set_skill("huifeng-bian", 140); 
        set_skill("suohou-shou",120);
        set_skill("hand",120);
        map_skill("hand","suohou-shou");
        map_skill("whip", "huifeng-bian");
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "huifeng-bian");
        prepare_skill("hand", "suohou-shou");
        
        set("chat_chance", 10);
        set("chat_msg_combat", ({
               (: perform_action, "whip.huixuan" :)
            }));

       
        create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "升袋" : "找你的舵主去。\n",
                "萧峰" : "哎，可惜可惜，乔帮主何等英雄，可惜是契丹种。\n",
                "乔帮主" : "啊？你是我们帮。。。乔大爷的朋友？\n"
                         "他是我们丐帮的前任帮主，一双降龙掌使得出神入化。\n"
                         "听说他以前每天都要喝十来二十斤酒下肚，\n"
                         "然后才去练掌，当真了不起！\n",
                "练掌" : "哦。。。这个我也不太清楚，他那时好象是跟奚长老学的。\n",
                "洪七公" : "呵呵，我也不太清楚他跑去哪偷吃了。\n",
                "捉蛇" : (: ask_job :),              
                "job" : (: ask_job :),
                "蛇阵" : (: ask_trap :),
                "放弃" : (: ask_fangqi :),
                "百草丹" : (: ask_dan :),
                "dan" : (: ask_dan :),
                "破布袋" : (: ask_whip :),
        ]));
        setup();
        carry_object("/kungfu/class/gaibang/obj/bainayi")->wear();
        carry_object("/kungfu/class/gaibang/obj/gb_budai9")->wear();
}

void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "丐帮" ) {
                command("say 丐帮可容不下你这种背信弃义的小人！");
                command("kill "+ob->query("id"));
                return;
        }
        if ( ob->query_int() < 25 ) {
                command(":)");
                command("say " + RANK_D->query_respect(ob) +"天资有限，跟我是学不好的。\n");
                return;
        }

        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("丐帮总舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","总舵");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}

void init()
{
        object me;
        me = this_player();
        
        ::init();
        if( interactive(me) && !is_fighting()&& me->query_temp("gb_snake/over"))
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}

void greeting(object ob)
{
        object snake;
        int exp,pot,potmax,poto,j;
        object me;
        
        potmax = ob->query("max_pot");
        me = this_object();
        j = ob->query("snake_job");

        if( !ob || environment(ob) != environment() ) return;
        if (!ob->query_temp("gb_snake/start")
                || !ob->query_temp("gb_snake/over"))
                return;

        if ( ob->query_temp("gb_snake/over")){
                if ( present("du she",environment(ob) ) 
                        && ob->query_temp("gb_snake/start")){
                        snake = present("du she",environment(ob));
                        }
                else 
                snake=present("du she",ob);
        }

        if (!snake && ob->query_temp("gb_snake/start")
                && ob->query_temp("gb_snake/over"))
        {
                command("angry " + ob->query("id"));
                command("say 这么简单的事都办不好，你下去吧。");
                ob->delete_temp("gb_snake");
                ob->apply_condition("job_busy",2+random(3));
                return;        
        }       
        if (snake && snake->query_temp("name1")==ob->query("id")
                && ob->query_temp("gb_snake/over"))
        { 
	        ob->add("snake_job",1);
                ob->delete_temp("gb_snake");
                
                exp = 200 + random(100);
                pot = exp/5 + random(exp/6);

             if (ob->query("snake_job") < 2000 || ob->query("combat_exp",1) < 2000000) {
                tell_object(ob, HIY"你获得了"+CHINESE_D->chinese_number(exp)+"点经验和"+CHINESE_D->chinese_number(pot)+"点潜能。\n"NOR);
                ob->add("combat_exp",exp);
                ob->add("potential",pot);
		poto = ob->query("potential");
                if (poto > potmax) ob->set("potential", potmax);
                write_file( "/log/job/snake_job",sprintf("%s %s(%s)第%d次捉蛇任务获得%d点经验，%d点潜能。\n",
                        ctime(time())[4..18],ob->name(),ob->query("id"),ob->query("snake_job"),exp,pot));
             } else
                write_file( "/log/job/snake_job",sprintf("%s %s(%s)第%d次捉蛇任务，没有得到奖励。当前经验：%d\n",
                        ctime(time())[4..18],ob->name(),ob->query("id"),ob->query("snake_job"),ob->query("combat_exp")));

                command("nod " +ob->query("id"));
                message_vision(HIM"陈长老从$P手里接过蛇，转身装进一个口袋里。\n"NOR,ob);
                message_vision(HIW"$N总共捉了"+CHINESE_D->chinese_number(ob->query("snake_job"))+"条蛇。\n"NOR,ob);
                destruct(snake);
                ob->apply_condition("job_busy",3+random(3));
        }
        if(!ob->query("gb/snaked") && j>1000){
                if(random(j)>1000 && !ob->query("gb/snake")) {
                        command("whisper " +ob->query("id")+" 想不想学玩蛇？");
                        message_vision(HIM"陈长老从布袋里拿出一条小蛇。吹了个口哨，只见小蛇马上如舞蹈状身子离地而起。\n"NOR,ob);
                        command("say 继续做吧，将来你对蛇性了解以后，我教你玩蛇的本事。");
                        command("pat " +ob->query("id"));
                        ob->set("gb/snake",1);
                        return;
                }

/*
                if(random(j)>2000 && ob->query("gb/snake")){
                        command("thumb " +ob->query("id"));
                        command("say 今天老叫化我格外高兴，传你一样拿手的本事。");
                        message_vision(HIM"陈长老从布袋里拿出一条小蛇。吹了个口哨，只见小蛇马上如舞蹈状身子离地而起。\n"NOR,ob);
                       	message_vision(HIM"陈长老递给$P一个笛子。\n"NOR,ob);
        		new("/clone/misc/gbzshao")->move(me);
                	command("whisper " +ob->query("id")+" 这个...这个...仔细看笛子。");
                        message_vision(HIM"$P听完连连点头道：师傅所言极是，某家真是茅舍顿开。\n"NOR,ob);
                        command("whisper " +ob->query("id")+" 你去苗疆后山，江湖郎中常去的那个地方抓条蛇自己玩吧。");
                        ob->set("gb/snaked",1);
                        return;
                }
*/
                command("say 继续做吧，将来你对蛇性了解以后，我教你玩蛇的本事。");
        }
        return;
}

int ask_job()
{
        object me,ob,name1,target,*living,where;
        string str;
        int i,j;
        me = this_player();
        
        if (me->query("family/family_name")!="丐帮" ){
                command("say 不用你帮我了，最近我手下弟子都很勤快。");
                return 1;
        }
        if (me->query("snake_job")>=2100 && me->query("combat_exp")>2000000){
                command("say 最近我手头的蛇足够了，你下去吧。\n");
                return 1;
        }
        if (me->query("combat_exp") < 100000){
                command("say 我看你笨手笨脚的，先去练练功夫吧。\n");
                return 1;
        }
        if (me->query_temp("gb_snake/start")){
                command("say 刚才不是让你帮我抓蛇去了吗，你怎么还不去？\n");
                return 1;
	}
        if (me->query_condition("job_busy")){
                command("say 你手头还有其他的事吧？过一会再来吧！\n");
                return 1;
        }
        if( me->query("job_name") =="丐帮抓蛇"){
        	command("say 你刚抓完蛇，还是先去休息一会吧。");
        	return 1;
        }

        living = livings();
        for (i=0;i < sizeof(living);i++){
                j = random(sizeof(living));
                if (j <= 1 || j == sizeof(living) -1) continue;
                if(check(living[j]) ){
                        target = living[j];
                        str = environment(target)->query("short");
                        where = environment(target);
                        if( str == "武僧堂" 
                         || str == HIR"心禅堂"NOR
                         || str == "金刚伏魔圈" ) continue;
                        if( get_place(base_name(environment(target)))!="" ) break;
                }
        } 

        if( !target )
                return notify_fail("陈长老暂时不想抓蛇，你过一会儿再来吧。\n");

        me->set_temp("gb_snake/start", 1);
        me->set_temp("gb_snake/where",get_place(base_name(environment(target)))+environment(target)->query("short"));
        me->apply_condition("job_busy", 9);
        me->set("job_name", "丐帮抓蛇");
        ob = new("/clone/animal/snake");
        name1 = me->query("id");
        ob->set_temp("name1",name1);
	ob->move(where);
        message_vision(CYN"陈长老说道：$N去"+me->query_temp("gb_snake/where")+CYN"附近帮我捉条蛇回来吧！\n"NOR,me);
        return 1;
}

int ask_trap()
{
        object ob, me = this_player();
        int i, j;
        object *obj;
        int x,y =0;

        if (present("qing she", me) || query("snake/"+me->query("id")) >0){
           command("say 还要？");
           command("heng");
           return 1;
        }
        obj = objects();
        x = sizeof(obj);
        while(i--) {
            if ( obj[i]->query("id") =="qing she" && obj[i]->query("owner") == me->query("id"))
            y++;
        } 
        if(y > 0){
           command("say 还要？");
           command("heng");
           return 1;
        }
        if (me->query("snake_job")<2000){
           command("say 多帮我抓点蛇，我才分你一些。");
           command("rascal");
           return 1;
        }
        j = random(3)+2;
        j = 1;
        for (i=0;i<=j;i++){
          ob = new("/clone/animal/trap-snake");
          ob->move(me);
          ob->set("owner",me->query("id"));
        }
        message_vision(HIG"$N给了$n几条小青蛇。\n"NOR,this_object(),me);
        me->add("snake_job",-j*2);
        add("snake/"+me->query("id"), 1);
        return 1;
}

string ask_fangqi()
{
        object me;

        me = this_player();
        
        if(me->query("family/family_name")!="丐帮")
              return "你非我丐帮英雄,跑这里瞎嚷嚷什麽?";
        if(!me->query_temp("gb_snake/start"))
              return "什么放弃？放什么弃？";

        me->delete_temp("gb_snake");
        me->clear_condition("job_busy");
        me->start_busy(3);
        me->apply_condition("job_busy",6+random(6));
        return "你帮不了我，那你就去练功吧。以后我再找你。";
}

string ask_dan()
{
        object me,ob;
        me = this_player();

         if(me->query("family/family_name")!= "丐帮")
                return "快去找医生吧，我可没办法！";
         if(query("dan_count") < 1)
                return "你来晚了，百草丹全部发完了，快去自己找大夫吧。";
        if (present("bai caodan", me))
                return RANK_D->query_respect(me) + 
                "百草丹很珍贵，你身上还有，还是留一些给其他帮中兄弟吧，丐帮弟子最讲义气！";
        if(me->query("snake_job")>100){
                ob = new("/d/gb/npc/obj/bcd");
                ob->move(me);
                message_vision("陈长老给$P一颗百草丹。\n",me);
                return "看在你帮我这么多次忙的份上，我就给你一颗。";
        }
         if((int)me->query("eff_jing",1)==(int)me->query("max_jing",1))
                return "你好象没有中毒嘛，来找我做什么？";

        add("yao_count", -1);
        ob = new("/d/gb/npc/obj/bcd");
        ob->move(me);
        message_vision("陈长老给$P一颗百草丹。\n",me);
        return "我这里有一颗百草丹，善解蛇虫杂毒，不知是否对你症况。";
}

string ask_whip()
{
        object me,ob;
        me = this_player();

        if (me->query("family/family_name")!="丐帮")
              	return "你非我丐帮英雄,跑这里瞎嚷嚷什麽?";
        if ( present("po budai", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "破布袋就在你身上！";
        if ( present("mumian jiasha", environment()) )
                return RANK_D->query_respect(this_player()) + 
                "破布袋就在这里任你取走。";
        ob = unew(BINGQI_D("pobudai"));
        if(!clonep(ob)) return "抱歉，你来晚了，破布袋已经给人取走了。";
        
        if(clonep(ob) && ob->violate_unique()){
           	destruct(ob);
           	return "抱歉，你来晚了，破布袋已经给人取走了。";
        }            
        ob->move(this_player());
        message_vision("\n陈长老递给$N一个破布袋。\n\n", this_player());
        return "这件破布袋就是你的了！";
}

string get_place(string str)
{ 
        string *place = explode(str, "/");

        str = "";
        if(place[0] == "d")
                switch(place[1]){
	                case "baituo":    str = "西域白驼山";  break;
                        case "hj":        str = "西域回疆"; break;
                        case "mingjiao":  str = "西域明教"; break;
                        case "shaolin":   str = "河南嵩山少林"; break;
                        case "songshan":  str = "河南嵩山"; break;
                        case "wudang":    str = "湖北武当山"; break;
                        case "xingxiu":   str = "西域星宿海"; break;
                        case "city":      str = "江南扬州城"; break;
                        case "emei":      str = "四川峨嵋山"; break;
                        case "fuzhou":    str = "南疆福州"; break;
                        case "jiaxing":   str = "江南嘉兴"; break;
                        case "taishan":   str = "山东泰山"; break;
                        case "dali":      str = "西南大理国"; break;
                        case "tls":       str = "大理天龙寺"; break;
                        case "tiezhang":  str = "湖南铁掌山"; break;
                        case "kunlun":    str = "";break;
                        case "fairyland": str = ""; break;
                        case "gumu":      str = ""; break;
                        case "chengdu":   str = "四川成都"; break;
                        case "huashan":   str = "陕西华山"; break;
                        case "xiangyang": str = "湖北襄阳"; break;
                        case "xueshan":   str = "西番大雪山"; break;
                        case "wizard":    str = ""; break;
                        case "death":     str = ""; break;
                        case "gaibang":   str = "丐帮分舵"; break;
                        case "hz":        str = "江南杭州"; break;
                        case "village":   str = "陕西小村"; break;
                        case "wuguan":    str = "襄阳武馆"; break;
                        case "thd":       str = ""; break;
                        case "gaibang":   str = "丐帮分舵"; break;
                        case "mr":        str = "苏州燕子坞"; break;
                        case "suzhou":    str = "苏州县城"; break;
                        case "sld":       str = "北海神龙岛"; break;
        }
        return str;
}

string *no_kill_list = ({
         "mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int check(object ob)
{
        object room;
        string room_name;
        
        if(!objectp(ob)
         || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
         || ob->query("env/invisibility")
         || ob->query("no_quest")
         || member_array(ob->query("id"), no_kill_list) != -1
         || userp(ob)
         || ob->query("attitude")=="aggressive"
         || ob->query("have_master")
         || ob->query("env/wimpy")
         || !objectp(room=environment(ob))
         || !room->query("outdoors")
         || room->query("no_fight") 
         || room->query("outdoors") == "昆仑翠谷"
         || strsrch(room_name = file_name(room),"/d/") != 0
         || strsrch(room_name, "/d/wizard/") == 0
         || strsrch(room_name, "/d/wuguan/") == 0
         || strsrch(room_name, "/d/death/") == 0
         || strsrch(room_name, "/d/kunlun/") == 0
         || strsrch(room_name, "/d/mingjiao/lsd/") == 0
         || strsrch(room_name, "/d/mingjiao/bhd/") == 0
         || strsrch(room_name, "/d/shaolin/liwu") == 0
         || strsrch(room_name, "/d/shaolin/houyuan") == 0
         || strsrch(room_name, "/d/huashan/jiabi") == 0
         || strsrch(room_name, "/d/shaolin/fumoquan") == 0
         || strsrch(room_name, "/d/shaolin/xinchan") == 0
         || strsrch(room_name, "/d/mingjiao/yuanzi") == 0
         || strsrch(room_name, "/d/mingjiao/wxiang") == 0
         || strsrch(room_name, "/d/baituo/") == 0
         || strsrch(room_name, "/d/thd/") == 0
         || strsrch(room_name, "/d/sld/") == 0) 
         return 0;
        return 1;
}
