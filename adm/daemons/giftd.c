/*
job_time/
String type 
官府 丐帮 华山 雪山 天地会 长乐帮 嵩山 送信 星宿
注意一些会减少数目次数的任务
*/
//by spiderii@ty 游戏初期为了吸引玩家，提高随机物品出现几率
#include <ansi.h>
//#define TT 50         // 每50次任务会出现随机奖励

#define BOOK    "/clone/gift/book"      //书
#define MIC     "/clone/gift/danwan"    //药
#define MON     "/clone/gift/money"     //钱
#define JADE    "/d/zhiye/obj/othermaterial" //玉
#define DAZAO   "/clone/gift/imbue"     //打造机会

inherit F_DBASE;

public string* Job_Type = ({
"刺杀","草料场","告急","抢劫","洪七公","少林熬粥","少林菜地","少林轮值",
"佛法降魔","明教巡逻","明教守卫","桃花岛","古墓护墓","古墓蜂巢","铁掌",
"慕容","看守铜鼎","峨嵋元兵","武馆","官府","丐帮","华山","雪山","天地会",
"长乐帮","嵩山","巡城","送信","星宿","武当","赵敏","大清国海战","神龙岛海战",
"护镖","少林救援","七窍玲珑"});

string* super_easy_list = ({"巡城",});

void give_gift(object who,string ob_name,string type,int times);

string* gifts = ({});

void create()
{
        seteuid(getuid());
        set("channel_id", "任务奖励精灵"); 
}

//flag  标志符
/*
奖励频率修正百分比
比如 50 则获得几率提高50%
*/
void check_count(object who,mixed ob,string type,int flag)
{
        int i,j;
        string ob_name;
        string* myjoblist;
        if(objectp(ob)) ob_name = ob->name();
        else if(stringp(ob)) ob_name = ob;
        
        myjoblist = who->query("myjoblist");
        if(!myjoblist || !arrayp(myjoblist) ) myjoblist= ({});
        
        while(member_array(type,myjoblist)!=-1)
        {
        	string* newmylist = ({});
        	j = 0;        	        	
        	for(i=0;i<sizeof(myjoblist);i++)
        	{
        		if(j)
        		{
        			newmylist += ({myjoblist[i]});
        			continue;
        		}
        		if(myjoblist[i]==type) j = 1;
        	}
        	myjoblist = newmylist;
        }
        myjoblist += ({type});
                        
        who->set("myjoblist",myjoblist);
                
        if (!type || member_array(type,Job_Type)== -1 )       return;
        
        if (!ob_name) return;
                
        if (!intp(i = who->query("job_time/"+type))) return;
        
        if (i <= 0)   return;
        if (i <= who->query("job_last_gift/"+type)) //已经领过奖品了
                return;
        if (who->is_robot())	return;
                
        //概率控制
        if ( who->is_vip() && who->query("kar") > 35) 
        	j = 100;
        
        else
        {
                if ( who->is_vip() ) j = 80;
                
                else
                {
                        if (who->query("kar") > 35) 
                        	j = 80;
                        else
                                j = 70;
                }
        }
        
        
        //easy job then...
        if( member_array(type,super_easy_list) != -1) flag -= 40;
        
        //grin robot
        if(who->is_robot()) j = j - 60;
                                                                
        j = j + j*flag/100;
        
        i = sizeof(myjoblist)-2;
                
        while(i>0)
        {
        	j = j + j*25/100;
        	i--;
        	//任务间隔越多 获奖几率越高
        }
                        
        i = who->query("job_time/"+type);
                   
        if (100 < 0) 
                give_gift(who,ob_name,type,i);
                
        return;                 
}

void ttttttt(string t)
{	
	check_count(previous_object(1),"神仙",t,0);
}

void give_gift(object who,string ob_name,string type,int times)
{
        //object ob  ob->name()   ob_name
        string msg = "";
        object obj;
        string str = "";
        int i = random(3);
        
        //check_dir();
        //obj = new(DIR+gifts[random(sizeof(gifts))]);
        if (type == "武馆"){
                obj = new (BOOK);
                str = "书";          
        }
//      else if(objectp(obj = WORKER_D->mater_random(who,0,0))) {str = "工匠物品";}
        else {
        int tt;	
        //int tt = random(2)?(random(2)?who->query("con"):who->query("int")):(random(2)?who->query("str"):who->query("dex"));        
        //tt += random(2)?(random(2)?who->query("con"):who->query("int")):(random(2)?who->query("str"):who->query("dex"));
        //一个人先天属性总和为80 所以随机取两个 hehehe
        //tt = tt * 10;
        tt = 100;
        //CHANNEL_D->do_channel( this_object(), "sys",sprintf("随机数字 = %d。",tt));
        if(who->query("job_time/"+type)%tt != 0) return;
        else
        {
        	switch(i) {

                        case 2:         
                                obj = new (MON);
                                str = "钱"; 
                                break;
                        default:return;
                }
                //10% 获得一次打造机会 或者玉
                if(random(10) > 100)
                {
                	int level=1;
                	i = random(2);
                	if(!random(5)) level+=1;
                	if(!random(5)) level+=1;
                	if(!random(5)) level+=1;
                	if(!random(7)) level+=1;
                	destruct(obj);
                	switch(i) {
                		case 0:
                			obj = new(DAZAO);
                			str = "天外陨石";
                			break;
                		case 1:
                			obj = new(JADE);
                			str = "玉";
                			obj->set_level(level);
                			break;
                		default:return;              			
                	}
                }
	}
}
	
        if (!objectp(obj))
        {
                CHANNEL_D->do_channel( this_object(), "sys",sprintf("%s出错。",str));
               // tell_object(who,"物品生成出错，请通知巫师。\n"); 不用让玩家看见 免得心寒
                return;
        }
        obj->set("gift_target",who->query("id"));
        obj->move(who);
        who->set("job_last_gift/"+type,times);
        //give了再set last_gift giggle
        switch(type)
                {                
                case "刺杀":
                	msg = "$N刚想离去路边出现一个老乞丐，$N突然想起这就是"
                	+ob_name+"\n"+ob_name+
                	"激动得握住了$N的手，说道：我代表千千万万大宋百姓感谢这位"
                	+RANK_D->query_respect(who)+
                	"，\n这"+ obj->query("unit") + obj->name()+
                	"是我走南闯北时意外获得就送给你啦！\n";
                	break;
                case "草料场":
                	msg = ob_name+"笑道：$N来得正巧！洪老帮主游走江湖，极难遇见，这次丐帮大会他赞你为我丐帮行了不少侠义之事，扬我丐帮侠义之名。\n"
                	+RANK_D->query_respect(who)+
                	"，这"+obj->query("unit") + obj->name()+"是他托我赠你的，望你牢记侠义之本！\n";
                	break;
               	case "告急":
               		msg = ob_name+"激动得握住了$N的手，说道：我代表千千万万大宋百姓感谢这位"
               		+RANK_D->query_respect(who)+
               		"，\n这"+ obj->query("unit") + obj->name()+"是我走南闯北时意外获得就送给你啦！\n";
               		break;
               	case "抢劫":
			msg = ob_name + "对$N赞叹不已：你小小年纪就劫掠了那么多财物。师父让我鼓励后辈师弟们，我看这" + 
			obj->query("unit") + obj->name()+"给你是再合适不过了。\n";
               		break;
               	case "洪七公":
               		msg = ob_name + "对你笑眯眯的说道：吃人家的嘴软。我老叫化居然已经吃了那么多娃娃孝敬的叫化鸡了。"+
               		"没法子，\n这"+obj->query("unit") + obj->name()+"就算一点小意思，老叫化也给肚皮一个交代吧！\n";
               		break;//npc ho7g
               	case "少林熬粥"://npc侍饭僧
               		msg = ob_name + "看了看你手上的老茧。叹道：小师弟你初入少林就如此勤修，太师叔叫我把这"+
               		obj->query("unit") + obj->name()+"留给努力的后辈僧人！如今就给了你吧！\n";
               		break;
               	case "少林菜地"://npc 缘根 
               		msg = ob_name + "狞笑道：看你个小秃驴干活还算卖力。上次佛爷爷我捡到这"+
               		obj->query("unit") + obj->name()+"，也不知道有什么用，就给了你吧！\n";
              		break;
               	case "少林轮值"://npc 慧修尊者
               		msg = ob_name + "叹道：师兄如此勤恳守寺护法，让人敬佩啊！这"+
               		obj->query("unit") + obj->name()+"我留着也没什么大用，就留给师兄吧！\n";
               		break;
               	case "佛法降魔"://npc xuan-du
               		msg = ob_name + "宣一声佛号：$N渡人无数，堪为沙门表率。此"+
               		obj->query("unit") + obj->name()+"老衲便可放心的传给你了。\n";
               		break;
               	case "明教巡逻"://wei yixiao
               		msg = ob_name + "紧紧握住了$N的手：守护我圣教，就要靠$N这样辛勤之辈。\n";
			msg += ob_name + "说道：$N为我教护卫工作出了不少力啦。这"+
			obj->query("unit") + obj->name()+"是教主让我赐予你的，望你继续努力，光大明教。\n";
               		break;
               	case "明教守卫"://chang yuchun
               		msg = ob_name + "紧紧握住了$N的手：守护我圣教，就要靠$N这样辛勤之辈。\n";
			msg += ob_name + "说道：$N为我教护卫工作出了不少力啦。这"+
			obj->query("unit") + obj->name()+"是教主让我赐予你的，望你继续努力，光大明教。\n";
               		break;
               	case "桃花岛"://xiao huang
               		msg = ob_name + "咯咯一笑：爹爹最讨厌只说不做的虚妄之徒。你却如此实干，为桃花岛做了这么多事情。爹爹必有夸赞。\n"+
               		"这"+obj->query("unit") + obj->name()+"是爹爹送我的，我就借花献佛，给了你吧。\n";
               		break;
               	case "古墓护墓"://孙婆婆
               		msg = ob_name + "上下打量了$N几眼。\n";
			msg += ob_name + "说道：$N守墓还算干得不赖。这"+
			obj->query("unit") + obj->name()+"就赏了你吧。务必再接再励，别就此松懈，知道了么？！\n";
               		break;
               	case "古墓蜂巢"://
               		msg = "你觉得工作辛苦，一屁股坐在地板上。忽然觉得地上有什么异物，一看，竟然是"+obj->query("unit") + obj->name()+
               		"。\n你欣喜若狂，捡了起来。";
               		break;
               	case "铁掌"://qiu qianren
               		msg = ob_name + "赞赏得拍了拍$N得肩膀：$N干得不错。也算是我铁掌后辈的佼佼者了，这"+
               		obj->query("unit") + obj->name()+"是我铁掌的宝物，就赐了你吧。\n";
               		break;
               	case "慕容"://murong fu
               		msg = ob_name + "对这$N长叹一声：若我慕容一族人人都能象$N你这样勤恳，大燕复国就不是梦想啦。这"+
               		obj->query("unit") + obj->name()+"你可拿去，或许日后有所帮助。也是我大燕幸事。\n";
               		break;
               	case "看守铜鼎"://yu daiyan
               		msg = ob_name + "赞许的拍拍$N的头。\n";
			msg = ob_name + "说道：你看守铜鼎多日，没有功劳，也有苦劳，我武当名门正派，讲究的就是心田。\n"+
			"这"+obj->query("unit") + obj->name()+"我留了多年，我一个废人有什么用，就送了你吧。\n";
               		break;
               	case "峨嵋元兵"://miejue shitai
               		msg = ob_name + "冷冷的瞪着$N。\n";
			msg = ob_name + "说道：干的还算不错，不过别就此骄傲了。这"+
			obj->query("unit") + obj->name()+"算我赐你的，但你若表现不好，我仍然要收回！\n";
               		break;              	               	
                case "武馆":
                        msg = ob_name+"对你笑道：本武馆虽然小，馆主为大家准备了一批新手入门书，这"+
                        obj->query("unit") + obj->name()+
                        "我看瞒适合你的，就送给你吧！\n";
                        break;
                case "官府":
                        msg = ob_name+"点了点头：$N为朝廷甘效犬马之劳这么久，忠心不二着实不易，这"+
                        obj->query("unit") + obj->name()+
                        "是朝廷给你的赏赐，跪谢圣恩吧！\n";
                        break;
                case "丐帮":
                        msg = ob_name+"笑道：$N来得正巧！洪老帮主游走江湖，极难遇见，"+
                        "这次丐帮大会他赞你为我丐帮行了不少侠义之事，扬我丐帮侠义之名。\n"
                        +RANK_D->query_respect(who)+"，这"+obj->query("unit") + obj->name()+
                        "是他托我赠你的，望你牢记侠义之本！\n";
                        break;
                case "华山":
                        msg = ob_name+"盯住$N上下打量几下，道：厉害厉害，多亏"+
                        RANK_D->query_respect(who)+
                        "华山周围才得以安宁，这"+obj->query("unit") + obj->name()+
                        "是我华山派经年所藏，就送给你了！\n";
                        break;
                case "雪山":
                        msg = ob_name+"拍了拍$N的头：你娃娃真是厉害，为我贡献了这么多美女，\n这个"+
                        obj->name()+
                        "是我前几天下山时候抢到的，看你为讨爷爷欢心，这么辛苦就送给你啦！\n";
                        break;
                case "天地会":
                        msg = ob_name+"激动的握住$N的手："+
                        RANK_D->query_respect(who)+
                        "，你屡次挫败鞑子的阴谋，解救我反清志士，以后反清复明就多多靠你了！\n这"
                        + obj->query("unit") + obj->name()+
                        "是前几天陈总舵主托我奖励你的，现在我把它给你！\n";
                        break;
                case "长乐1帮":
                        msg = ob_name+"看了看$N长途奔波后的倦容，沉吟半晌：嗯，你为我长乐帮奋力击杀不少敌人的高手，\n" + 
                        "这许多事，本总管心里是有数的，这"+
                        obj->query("unit") + obj->name()+
                        "是我心爱之物，你拿去吧！\n";
                        break;
                case "嵩山":
                        msg = ob_name+"紧紧的握住了$N的手：五岳统一的大事，旁人阻挠甚多，难得" +
                        RANK_D->query_respect(who)+
                        "你深明大义这么热心，为我五岳联盟之事奔波，\n这" + 
                        obj->query("unit") + obj->name()+"是我嵩山派前辈遗物，你拿去吧！\n";
                        break;
                case "巡城":
                        msg = ob_name+"紧紧的握住了$N的手：这位小兄弟，难得" +
                        RANK_D->query_respect(who)+
                        "你为我大理巡城，\n这"+ obj->query("unit") + obj->name() +
                        "我也无甚大用，你就拿去吧！\n";
                        break;
                case "送信":
                	    msg = ob_name+"拆开信件，仔细阅览，只见脸色越是凝重，阅毕长叹一声：" +
                	    "这封信件对我甚是重要，解开了多年萦绕我心头的谜团。\n难得$N千辛万苦为我送来，这"
                	    + obj->query("unit") + obj->name()+
                	    "我收藏多年，现在就送给你吧，后会有期！\n";
                        break;
                case "星宿":
                        msg = ob_name+"捻着胡须，闭着眼睛听完你的溜须拍马，满意的拍了拍$N的头。\n" + 
                        "小娃娃脑袋就是活络，为老仙我歌功颂德，竭尽所能，当知我老仙也不会亏待你吧！\n这"+
                        obj->query("unit") + obj->name()+"是我搜索星宿海方圆数里所得，" + 
                        "看你这么讨老仙我欢心就送给你啦！\n";
                        break;
                case "武当":
                        if (str == "药"||str == "极品药")
                                msg = ob_name+"点了点头：$N为我武当派做了这么多事，没有功劳也有苦劳！\n" + 
                                "这"+ obj->query("unit") + obj->name()+
                                "可是武当练丹房炼得的极品，你这就拿去，服用后当有奇效！\n";
                        else
                                msg = ob_name+"点了点头："+who->query("name")+
                                "，为我武当派做了这么多事，着实不易，这" +
                                obj->query("unit") + obj->name() + 
                                "可是我师尊张真人给我的，\n现送给你，对你百尺竿头更进一步必有裨益！\n";
                        break;
                case "赵敏":
                        msg = ob_name+"很调皮的拍了拍$N的头，说道：不错！不错！，" +
                        "你为我做了这么多事，我也不会亏待你！\n这"+ obj->query("unit") + 
                        obj->name()+"是我前几天来中原所得，看你这么尽心尽力就送给你啦！\n";
                        break;
                case "大清国海战":
                        msg = ob_name+"紧紧的握住了$N的手，说道：不错！不错！，" + 
                        RANK_D->query_respect(who) + 
                        "为我大清国出了这么多力，我也不会亏待你！\n这" + 
                        obj->query("unit") + obj->name() + 
                        "是康熙爷给我的，看你这么卖力就送给你啦！\n";
                        break;
                case "神龙岛海战":
                        msg = ob_name + "紧紧的握住了$N的手，说道：不错！不错！，" + 
                        RANK_D->query_respect(who) + 
                        "为我洪教主出了这么多力，我也不会亏待你！\n这" + 
                        obj->query("unit") + obj->name() + 
                        "是洪教主赐给我的，看你这么卖力就送给你啦！\n";
                        break;
                case "护1镖":
                        msg = ob_name + "紧紧的握住了$N的手，说道：不错！不错！，" + 
                        RANK_D->query_respect(who)+"为我福威镖局押送了这么多次镖，我也不会亏待你！\n这" +
                        obj->query("unit") + obj->name() + 
                        "是我多年珍藏，看你这么卖力就送给你啦！\n";
                        break;
                case "少林救援":
                	msg = ob_name+"紧紧的握住了$N的手，说道：这次破解恒山被围，" + 
                	RANK_D->query_respect(who) + "的功劳甚大！\n这" +
                	obj->query("unit") + obj->name() + 
                	"是我始祖留给我的宝物，看来你可以继承它！\n"; 
                	break;
                case "七窍玲珑":                	
                	msg = ob_name+"忽然想起了什么，高声叫道：「请留步」。\n"+
                	ob_name+"说道：「"+
                	ob_name+"劳累"+RANK_D->query_respect(who)+"，我全真无以回报，这里还有一"+
                	obj->query("unit") + obj->name() + 
                	"，是去岁我师弟丘处机云游时带来的，我也没什么用，就送你吧。」";
                default:
        }
/*      message_vision(msg+ob_name+"给$N一"+ obj->query("unit")+obj->name()+"。\n",who);
        message_vision(ob_name+"顺手又给了$N几枚书剑通宝。\n",who);
        who->add("SJ_Credit",5+random(5));  */

        if (type != "武馆")
        	CHANNEL_D->do_channel( this_object(), "rumor",sprintf("听说%s从%s处获得了一%s！",who->query("name"),ob_name, obj->query("unit") + obj->name()));
        
        if (type != "武馆")
        log_file("job/PRIZE",
                sprintf("%s第%d次%s任务获得%s奖励。", 
                who->name(1)+"("+getuid(who)+")",
                who->query("job_time/"+type),
                type,str
                ),who
                );
}
