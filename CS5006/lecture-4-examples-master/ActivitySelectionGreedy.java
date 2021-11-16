import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.TreeSet;

/**
 * 
 */

/**
 * Demonstration of greedy algorithm for selecting activities.
 *
 * @author philip gust
 */
public final class ActivitySelectionGreedy {
	/**
	 * Activity from start to finish inclusive
	 */
	public static final class Activity {
		/** start time */
		public final int start;
		/** finish time */
		public final int finish;
		
		/** 
		 * Create activity with give start and finish times
		 * 
		 * @param start start time
		 * @param finish finish time
		 */
		public Activity(int start, int finish) { 
			if (start < 0 || start > finish) {
				throw new IllegalArgumentException();
			}
			this.start = start; 
			this.finish = finish;
		}
		/**
		 * Returns the duration of the activity.
		 * 
		 * @return the duration of the activity
		 */
		public int duration() {
			return finish-start;
		}
		/**
		 * Determines whether two activities are equal based on start and finish
		 * @param obj the other object
		 * @return true if the two activities have same start and finish
		 */
		@Override
		public boolean equals(Object obj) {
			return 	   (obj instanceof Activity)
					&& (((Activity)obj).start == start)
					&& (((Activity)obj).finish == finish);
		}
	}
	
	/**
	 * Activity set that orders activities by ascending finish,
	 * then by descending duration to maximize time in activities.
	 */
	@SuppressWarnings("serial")
	public static final class ActivitySet extends TreeSet<Activity> {
		/**
		 * Create set of activities from activities.
		 * @param activities the activities to initialize the set
		 */
		public ActivitySet(Activity ... activities) {
			this(Arrays.asList(activities));
		}
		
		/**
		 * Create set of activities from collection of activities.
		 * @param activities a collection of activities to initialize the set
		 */
		public ActivitySet(Collection<Activity> activities) {
			// create set with comparator by ascending finish,
			// then by descending duration
			super(new Comparator<Activity>() {
				public int compare(Activity act1, Activity act2) {
					if (act1.finish == act2.finish) {
						// compare durations if finish times same
						return act1.duration() - act2.duration();
					}
					return act1.finish - act2.finish;
				}
			});
			addAll(activities);
			
		}
	}

	/**
	 * Greedy algorithm selects maximum number of non-overlapping activities.
	 * @param activities collection of activities sorted by earliest finish
	 * @return selected collection of non-overlapping activities in order
	 */
	public static Collection<Activity> selectActivities(ActivitySet activities) {
		Collection<Activity> selected = new ArrayList<Activity>();
		Activity lastSelected = null;
		for (Activity activity : activities) {
			if (   (lastSelected == null) 
				|| (activity.start >= lastSelected.finish)) {
				selected.add(activity);
				lastSelected = activity;
			}
		};
		return selected;
	}

	/**
	 * Print the selected activities.
	 *
	 * @param activities the selected activities
	 */
	public static void printActivities(Collection<Activity> activities) {
		System.out.print("Selected activities:");
		if (activities.isEmpty()) {
			System.out.print(" none");
		}
		String sep = "";
		for (Activity activity : activities) {
			System.out.printf("%s {%d,%d}", sep, activity.start, activity.finish);
			sep = ",";
		}
		System.out.println();
	}

	/**
	 * Select best activities from a list of possible activities.
	 *
	 * @param args unused
	 */
	public static void main(String[] args) {
		ActivitySet activities = new ActivitySet(
				new Activity(1,2), new Activity(3,4), new Activity(0,6), 
				new Activity(5,7), new Activity(8,9), new Activity(5,9), 
				new Activity(7,9), new Activity(7,8)
		);
		Collection<Activity> selected = selectActivities(activities);
		printActivities(selected);
	}
}
